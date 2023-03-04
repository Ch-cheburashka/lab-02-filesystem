#include "custom_iterator/custom_iterator.hpp"
#include <task_1/task_1.hpp>

using path = std::filesystem::path;

void print_help(std::string &&s) {
    std::cout << "USAGE: " << s << "\n";
}

int main(int argc, char **argv) {

    iterating(R"(/mnt/d/projects/lab-02-filesystem/misc/ftp/)", false);

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