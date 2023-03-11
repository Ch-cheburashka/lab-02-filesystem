//
// Created by baran on 05.03.2023.
//

#ifndef SIGNATURE_ANALYSER_TASK_1_HPP
#define SIGNATURE_ANALYSER_TASK_1_HPP

#include <filesystem>
#include <broker/broker.hpp>

using path = std::filesystem::path;

std::vector<broker> brokers_gatherer (const std::filesystem::path& path);

void report_printer (const std::vector<broker>& brokers, bool files_output);

#endif //SIGNATURE_ANALYSER_TASK_1_HPP
