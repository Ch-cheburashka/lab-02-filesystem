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
    static bool filename_analyzer(const std::string &s);
    static std::string broker_seeker(const std::string &s);
    static std::string date_seeker(const std::string &s);
    static std::string account_seeker(const std::string &s);
    static std::map<std::string, std::vector<std::string>> report_printer (const std::string &s,size_t indent);
    static void iterating(const path &p, bool print);
};


#endif //SIGNATURE_ANALYSER_CUSTOM_ITERATOR_HPP
