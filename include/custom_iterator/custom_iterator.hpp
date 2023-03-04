#ifndef SIGNATURE_ANALYSER_CUSTOM_ITERATOR_HPP
#define SIGNATURE_ANALYSER_CUSTOM_ITERATOR_HPP
#include <string>
#include <filesystem>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <iostream>

using path = std::filesystem::path;
class custom_iterator {
public:
    custom_iterator(std::map<std::string, std::vector<std::string>> broker, size_t indent, std::string path_str);
    static bool filename_analyzer(const std::string &s);
    static std::string broker_seeker(const std::string &s);
    static std::string date_seeker(const std::string &s);
    static std::string account_seeker(const std::string &s);
    std::map<std::string, std::vector<std::string>> get_broker ();

private:
    std::map<std::string, std::vector<std::string>> _broker;
    size_t _indent;
    std::string _path_str;
};


#endif //SIGNATURE_ANALYSER_CUSTOM_ITERATOR_HPP
