#include "Day06.h"
#include <iostream>
#include <ranges>
#include <algorithm>
#include <expected>

constexpr auto indexOfUniqueString(const std::string_view message, const std::size_t uniqueLength) -> std::size_t {
    auto dups = std::array<int, 26> { };
    auto dupCount = 0;

    for(std::size_t i = 0; i < message.size(); ++i) {
        const auto lastIndex = message[i]- 97;
        dups[lastIndex] += 1;
        dupCount += dups[lastIndex] > 1;

        if (dupCount == 0 && i >= uniqueLength - 1) return i + 1;

        const auto firstIndex = message[i - (uniqueLength - 1)] - 97;
        dups[firstIndex] -= (i >= uniqueLength - 1);
        dupCount -= (dups[firstIndex] >= 1) * (i >= uniqueLength - 1);
    }
}

auto Day06::partOneAlt(std::string& input) -> size_t {
    return indexOfUniqueString(input, 4);
}

auto Day06::partTwoAlt(std::string& input) -> size_t {
    return indexOfUniqueString(input, 14);
}