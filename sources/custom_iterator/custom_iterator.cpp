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

custom_iterator::custom_iterator(std::map<std::string, std::vector<std::string>> broker, size_t indent, std::string path_str) : _broker(broker), _indent(indent), _path_str(path_str) {
    for (size_t i = 0; i < _path_str.length(); i += _indent) {
        _broker.emplace(custom_iterator::account_seeker(_path_str.substr(i, _indent-1)), std::vector<std::string>{});
        if (custom_iterator::account_seeker(_path_str.substr(i, _indent)) == custom_iterator::account_seeker(_path_str.substr(i + _indent - 1, _indent))) {
            _broker.at(custom_iterator::account_seeker(_path_str.substr(i, _indent-1))).emplace_back(
                    custom_iterator::date_seeker(_path_str.substr(i, _indent)));
        }
        else
            _broker.emplace(custom_iterator::account_seeker(_path_str.substr(i, _indent)), std::vector<std::string>{});
    }
}

std::map<std::string, std::vector<std::string>> custom_iterator::get_broker() {
    return this->_broker;
}