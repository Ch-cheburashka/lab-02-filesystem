#include <task_1/task_1.hpp>
#include <custom_iterator/custom_iterator.hpp>
#include <constants.hpp>

std::string broker_seeker(const path &p) {
    std::string res, cur = p.string();
    for (size_t i = cur.find("ftp") + 4; cur[i] != '/'; ++i) {
        res += cur[i];
    }
    return res;
}

bool filename_analyzer(const std::string &s) {
    std::vector<std::string> components = custom_iterator::components_extractor(s);
    if (components[1].length() == 8 && components[2].length() == 8 && components[3] == ".txt" &&
        components[0].erase(0,s.find(broker_seeker(components[0])) + broker_seeker(components[0]).length() +1) ==
        "balance")
        return true;
    return false;
}

void report_printer(custom_iterator &&c, const std::string &br) {
    for (auto &i: c.get_broker()) {
        std::cout << "broker:" << br << " account:" << i.first << " files:" << i.second.size() << " lastdate: "
                  << i.second[i.second.size() - 1] << "\n";
    }
}

void iterating(const path &p, bool print) {
    std::string list;
    std::string res, ib_s, bcs_s, otk_s;
    for (auto &entry: std::filesystem::directory_iterator{p}) {
        if (entry.is_directory()) {
            if (print)
                iterating(entry.path(), true);
            else
                iterating(entry.path(), false);
        }
        if (entry.is_directory() || !filename_analyzer(entry.path().string())) {
            continue;
        }
        if (print)
            std::cout << broker_seeker(entry.path().string()) << " "
                      << entry.path().string().erase(0, entry.path().string().find("balance")) << std::endl;
        else {
            list += broker_seeker(entry.path().string()) + " " +
                    entry.path().string().erase(0, entry.path().string().find("balance")) + '\n';
        }
    }
    if (!print) {
        for (size_t i = 0; i < list.length(); ++i) {
            if (list.substr(i, BCS_BR_INDENT) == BCS_STR) {
                bcs_s.append(list.substr(i, BCS_LINE_INDENT));
            }
            if (list.substr(i, IB_BR_INDENT) == IB_STR) {
                ib_s.append(list.substr(i, IB_LINE_INDENT));
            }
            if (list.substr(i, OTK_BR_INDENT) == OTK_STR) {
                otk_s.append(list.substr(i, OTK_LINE_INDENT));
            }
        }
        std::map<std::string, std::vector<std::string>> map_bcs;
        custom_iterator ci_bcs(map_bcs, BCS_LINE_INDENT, bcs_s);
        report_printer(ci_bcs.info_gatherer(), BCS_STR);

        std::map<std::string, std::vector<std::string>> map_ib;
        custom_iterator ci_ib(map_ib, IB_LINE_INDENT, ib_s);
        report_printer(ci_ib.info_gatherer(), IB_STR);

        std::map<std::string, std::vector<std::string>> map_otk;
        custom_iterator ci_otk(map_otk, OTK_LINE_INDENT, otk_s);
        report_printer(ci_otk.info_gatherer(), OTK_STR);
    }
}
