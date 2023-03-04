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
    [[nodiscard]] std::map<std::string, std::vector<std::string>> get_broker ();
    custom_iterator info_gatherer ();
    static std::vector<std::string> components_extractor(const path &p);

private:
    std::map<std::string, std::vector<std::string>> _broker;
    size_t _indent;
    std::string _path_str;
};


#endif //SIGNATURE_ANALYSER_CUSTOM_ITERATOR_HPP
