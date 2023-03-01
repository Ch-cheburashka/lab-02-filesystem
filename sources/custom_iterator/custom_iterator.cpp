#include <custom_iterator/custom_iterator.hpp>

bool custom_iterator::filename_analyzer(const std::string &s) {
    if (s.find("old.txt") != std::string::npos || s.find("balance") == std::string::npos ||
        s.substr(s.length() - 4, s.length()) != ".txt") {
        return false;
    }
    return true;
}

std::string custom_iterator::broker_seeker(const std::string &s) {
    std::string res;
    for (size_t i = s.find("ftp") + 4; s[i] != '/'; ++i) {
        res += s[i];
    }
    return res;
}

std::string custom_iterator::date_seeker(const std::string &s) {
    std::string res;
    for (size_t i = s.find_last_of('_') + 1; s[i] != '.'; ++i) {
        res += s[i];
    }
    return res;
}

std::string custom_iterator::account_seeker(const std::string &s) {
    std::string res;
    for (size_t i = s.find("balance") + 8; s[i] != '_'; ++i) {
        res += s[i];
    }
    return res;
}

std::map<std::string, std::vector<std::string>> custom_iterator::report_printer(const std::string &s, size_t indent) {
    std::map<std::string, std::vector<std::string>> map;
    for (size_t i = 0; i < s.length(); i += indent) {
        map.emplace(custom_iterator::account_seeker(s.substr(i, indent-1)), std::vector<std::string>{});
        if (custom_iterator::account_seeker(s.substr(i, indent)) == custom_iterator::account_seeker(s.substr(i + indent - 1, indent))) {
            map.at(custom_iterator::account_seeker(s.substr(i, indent-1))).emplace_back(
                    custom_iterator::date_seeker(s.substr(i, indent)));
        }
        else
            map.emplace(custom_iterator::account_seeker(s.substr(i, indent)), std::vector<std::string>{});
    }
    return map;
}

void custom_iterator::iterating(const path &p, bool print) {
    std::string list, res, ib_s, bcs_s, otk_s;
    for (auto &entry: std::filesystem::directory_iterator{p}) {
        if (entry.is_directory()) {
            if (print)
                iterating(entry.path(), true);
            else
                iterating(entry.path(), false);
        }
        if (!custom_iterator::filename_analyzer(entry.path().string()) || entry.is_directory()) {
            continue;
        }
        if (print)
            std::cout << custom_iterator::broker_seeker(entry.path().string()) << " "
                      << entry.path().string().erase(0, entry.path().string().find("balance")) << std::endl;
        else {
            list.append(custom_iterator::broker_seeker(entry.path().string()) + " " +
                        entry.path().string().erase(0, entry.path().string().find("balance")) + '\n');
        }
    }
    if (!print) {
        for (size_t i = 0; i < list.length(); ++i) {
            if (list.substr(i, 3) == "bcs") {
                bcs_s.append(list.substr(i, 34));
            }
            if (list.substr(i, 2) == "ib") {
                ib_s.append(list.substr(i, 33));
            }
            if (list.substr(i, 8) == "otkritie") {
                otk_s.append(list.substr(i, 39));
            }
        }
        std::map<std::string, std::vector<std::string>> bcs_ac = custom_iterator::report_printer(bcs_s,34);
        for (auto& i : bcs_ac) {
            std::cout << "broker:bsc account:" << i.first << " files:" << i.second.size() << " lastdate: " << i.second[i.second.size()-1] << "\n";
        }

        std::map<std::string, std::vector<std::string>> ib_ac = custom_iterator::report_printer(ib_s,33);
        for (auto& i : ib_ac) {
            std::cout << "broker:ib account:" << i.first << " files:" << i.second.size() << " lastdate: " << i.second[i.second.size()-1] << "\n";
        }

        std::map<std::string, std::vector<std::string>> otk_ac = custom_iterator::report_printer(otk_s,39);
        for (auto& i : otk_ac) {
            std::cout << "broker:otkritie account:" << i.first << " files:" << i.second.size() << " lastdate: " << i.second[i.second.size()-1] << "\n";
        }
    }
}
