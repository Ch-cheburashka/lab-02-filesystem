#include <custom_iterator/custom_iterator.hpp>

std::vector<std::string> custom_iterator::components_extractor(const path &p) {
    std::vector<std::string> components;
    std::string s = p.string();
    for (auto it = s.find('_'); it != std::string::npos; s = s.substr(it + 1), it = s.find('_')) {
        components.push_back(s.substr(0, it));
    }
    components.push_back(s.substr(0,s.find('.')));
    if (components.size() > 1)
        components.push_back(s.substr(s.find('.'),s.length()));
    return components;
}

custom_iterator::custom_iterator(std::map<std::string, std::vector<std::string>> broker, size_t indent,
                                 std::string path_str) : _broker(broker), _indent(indent), _path_str(path_str) {}


custom_iterator custom_iterator::info_gatherer () {
    for (size_t i = 0; i < _path_str.length(); i += _indent) {
        std::vector<std::string> components = components_extractor(_path_str.substr(i, _indent));
        std::vector<std::string> next_components = components_extractor(_path_str.substr(i + _indent - 1, _indent));
        _broker.emplace(components[1], std::vector<std::string>{});
        if (components[1] == next_components[1]) {
            _broker.at(components[1]).emplace_back(components[2]);
        } else
            _broker.emplace(components[1], std::vector<std::string>{});
    }
    return *this;
}

std::map<std::string, std::vector<std::string>> custom_iterator::get_broker() {
    return this->_broker;
}