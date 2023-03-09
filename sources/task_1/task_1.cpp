#include <task_1/task_1.hpp>
#include <algorithm>
#include <iostream>
#include <vector>
#include <broker/broker.hpp>

std::vector<std::string> components_extractor(const path &p) {
    std::vector<std::string> components;
    std::string s = p.string();
    for (auto it = s.find('_'); it != std::string::npos; s = s.substr(it + 1), it = s.find('_')) {
        components.push_back(s.substr(0, it));
    }
    components.push_back(s.substr(0, s.find('.')));
    if (components.size() > 1)
        components.push_back(s.substr(s.find('.'), s.length()));
    return components;
}

std::filesystem::path last_date_seeker (const std::list<path>& files) {
    path max_file = files.front();
    auto max_comp = components_extractor(max_file);
    for (auto& i : files) {
        auto cur_comp = components_extractor(i);
        if (std::stoi(cur_comp[2]) > std::stoi(max_comp[2])) {
            max_comp = cur_comp;
            max_file = i;
        }
    }
    return max_file;
}

std::string broker_seeker(const path &p) {
    std::string res, cur = p.string();
    for (size_t i = cur.find("ftp") + 4; cur[i] != '/'; ++i) {
        res += cur[i];
    }
    return res;
}

bool filename_analyzer(const std::string &s) {
    std::vector<std::string> components = components_extractor(s);
    if (components[1].length() == 8 && components[2].length() == 8 && components[3] == ".txt" &&
        components[0].erase(0, s.find(broker_seeker(components[0])) + broker_seeker(components[0]).length() + 1) ==
        "balance")
        return true;
    return false;
}

std::vector<broker> brokers_gatherer (const std::filesystem::path& path) {
    std::vector<broker> brokers;
    auto cur_it = begin(std::filesystem::directory_iterator{path});
    auto cur_path = path;
    auto cur_dir = begin(std::filesystem::directory_iterator{path});
    while (true) {
        if (cur_it == end(std::filesystem::directory_iterator{cur_path})) {
            cur_dir++;
            if (cur_dir == end(std::filesystem::directory_iterator{cur_path}))
                break;
            cur_it = begin(cur_dir);
            cur_path = cur_it->path();
            continue;
        }
        if (cur_it->is_regular_file() && filename_analyzer(cur_it->path())) {
            std::string br = broker_seeker(cur_it->path());
            auto components = components_extractor(cur_it->path());
            if (brokers.empty() || std::find_if(brokers.begin(), brokers.end(),
                                                [&br](const broker &broker) { return broker._name == br; }) ==
                                   brokers.end()) {
                std::list<std::filesystem::path> files;
                files.push_back(cur_it->path());
                account ac(components[1], files);
                std::vector<account> accounts;
                accounts.emplace_back(ac);
                brokers.emplace_back(br, accounts);
            } else {
                size_t broker_index = 0;
                for (; broker_index < brokers.size(); ++broker_index) {
                    if (brokers[broker_index]._name == broker_seeker(cur_it->path()))
                        break;
                }
                auto accounts = brokers[broker_index]._accounts;
                std::string ac = components[1];
                if (accounts.empty() || std::find_if(accounts.begin(), accounts.end(),
                                                     [&ac](const account &account) { return account._name == ac; }) == accounts.end()) {
                    std::list<std::filesystem::path> files;
                    files.push_back(cur_it->path());
                    brokers[broker_index]._accounts.emplace_back(ac, files);
                } else {
                    for (size_t account_index = 0; account_index < accounts.size(); ++account_index) {
                        if (accounts[account_index]._name == components[1]) {
                            brokers[broker_index]._accounts[account_index]._files.push_back(cur_it->path());
                            break;
                        }
                    }
                }
            }
        }
        if (cur_it->is_directory()) {
            cur_path = cur_it->path();
            cur_it = std::filesystem::directory_iterator{cur_it->path()};
            continue;
        }
        cur_it++;
    }
    return brokers;
}

void report_printer (const std::vector<broker>& brokers) {
    for (auto &broker: brokers) {
            for (auto &account : broker._accounts) {
                auto components = components_extractor(last_date_seeker(account._files));
                std::cout << "broker:" << broker._name << " account:" << account._name << " files:"
                          << account._files.size() << " lastdate:" << components[2] << "\n";
            }
        }
}

void files_output (const std::vector<broker>& brokers) {
    for (auto &broker: brokers) {
        for (auto &account : broker._accounts) {
            auto components = components_extractor(last_date_seeker(account._files));
            for (auto &file : account._files) {
                std::cout << broker._name << " " << file.string().erase(0, file.string().find("balance")) << "\n";
            }
        }
    }
}