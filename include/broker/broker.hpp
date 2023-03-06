
#ifndef SIGNATURE_ANALYSER_BROKER_HPP
#define SIGNATURE_ANALYSER_BROKER_HPP

#include <vector>
#include <filesystem>
#include <string>
#include <list>

struct account {
    std::string _name;
    std::list<std::filesystem::path> _files;

    account(std::string name, std::list<std::filesystem::path> files);
};

struct broker {
    std::string _name;
    std::vector<account> _accounts;

    broker(std::string name, std::vector<account> accounts);
};

#endif //SIGNATURE_ANALYSER_BROKER_HPP
