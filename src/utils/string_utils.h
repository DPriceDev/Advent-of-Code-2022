#ifndef ADVENT_OF_CODE_2022_CPP_STRING_UTILS_H
#define ADVENT_OF_CODE_2022_CPP_STRING_UTILS_H

#include <string>
#include <vector>
#include <ranges>

namespace string {

    auto splitString(const std::string_view toSplit, const char delimiter) -> std::vector<std::string_view> {
        auto output = std::vector<std::string_view> { };
        for (const auto token : toSplit | std::views::split(delimiter)) {
            output.emplace_back(token);
        }
        return output;
    }

}

#endif // ADVENT_OF_CODE_2022_CPP_STRING_UTILS_H
