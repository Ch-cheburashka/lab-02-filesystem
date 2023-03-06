#include "broker/broker.hpp"

broker::broker(std::string name, std::vector<account> accounts)  : _name(name), _accounts(accounts) {}

account::account(std::string name, std::list<std::filesystem::path> files)  : _name(name), _files(files) {}
