#include "custom_iterator/custom_iterator.hpp"

using path = std::filesystem::path;

void report_printer (custom_iterator &&c,const std::string& br) {
    for (auto& i : c.get_broker()) {
        std::cout << "broker:" << br << " account:" << i.first << " files:" << i.second.size() << " lastdate: " << i.second[i.second.size()-1] << "\n";
    }
}

void iterating(const path &p, bool print) {
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
        std::map <std::string, std::vector<std::string>> map_bcs;
        report_printer({map_bcs,34,bcs_s},"bcs");

        std::map<std::string, std::vector<std::string>> map_ib;
        report_printer({map_ib,33,ib_s},"ib");

        std::map<std::string, std::vector<std::string>> map_otk;
        report_printer({map_ib,33,ib_s},"otkritie");
    }
}

void print_help(std::string &&s) {
    std::cout << "USAGE: " << s << "\n";
}

int main(int argc, char **argv) {

    if (argc > 3 || (argc < 3 && argc > 1)) {
        print_help("WRONG NUMBER OF ARGUMENTS");
        return 1;
    }
    path p;
    if (argc == 1) {
        p = std::filesystem::current_path();
    } else {
        p = argv[1];
    }
    if (!exists(p)) {
        print_help("PATH DOES NOT EXIST");
        return 1;
    }
    if (strcmp("-p", argv[2]) == 0) {
        iterating(p, true);
    } else if (strcmp("-r", argv[2]) == 0) {
        iterating(p, false);
    }
    return 0;
}