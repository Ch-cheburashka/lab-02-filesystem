#include <task_1/task_1.hpp>
#include <iostream>
#include <cstring>

using path = std::filesystem::path;

void print_help(std::string &&s) {
    std::cout << "USAGE: " << s << "\n";
}

int main(int argc, char **argv) {

    if (argc != 2 && argc != 3) {
        print_help("WRONG NUMBER OF ARGUMENTS");
        return 1;
    }
    path p;
    if (argc == 2) {
        p = std::filesystem::current_path();
    } else {
        p = argv[1];
    }
    if (!exists(p)) {
        print_help("PATH DOES NOT EXIST");
        return 1;
    }
    if (strcmp("-p", argv[argc-1]) == 0) {
        iteration(p, true);
    } else if (strcmp("-r", argv[argc-1]) == 0) {
        iteration(p, false);
    }
    return 0;
}