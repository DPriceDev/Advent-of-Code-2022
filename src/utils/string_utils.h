#ifndef ADVENT_OF_CODE_2022_CPP_STRING_UTILS_H
#define ADVENT_OF_CODE_2022_CPP_STRING_UTILS_H

#include <string>
#include <vector>
#include <ranges>

namespace string {
    auto splitString(std::string_view toSplit, char delimiter) -> std::vector<std::string_view>;

    auto toInt(std::string_view input) -> long;
}

#endif // ADVENT_OF_CODE_2022_CPP_STRING_UTILS_H
