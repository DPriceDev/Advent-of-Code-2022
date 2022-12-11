#ifndef ADVENT_OF_CODE_2022_CPP_FILE_UTILS_H
#define ADVENT_OF_CODE_2022_CPP_FILE_UTILS_H

#include <fstream>
#include <vector>

namespace file {
    auto getLines(const std::string& filename) -> std::vector<std::string>;
    auto readText(const std::string& filename) -> std::string;
}

#endif // ADVENT_OF_CODE_2022_CPP_FILE_UTILS_H
