#include <iostream>
#include <vector>
#include <functional>
#include <array>
#include <numeric>
#include "file_utils.h"

constexpr auto getPriority(const char& letter) -> int {
    const auto asciiValue = static_cast<int>(letter ^ ' ');
    return asciiValue - 64 - ((asciiValue / 91) * 6);
}

constexpr auto findMatchingTypesIn(std::vector<std::string_view>&& lines) -> int {
    std::array<int, 52> types { };

    for (std::size_t index = 0; index < lines.size() - 1; ++index) {
        for (const auto& letter : lines[index]) {
            const auto priority = getPriority(letter);
            if (types[priority - 1] == index) types[priority - 1] += 1;
        }
    }

    const auto line = lines.back();
    return std::accumulate(line.begin(), line.end(), 0, [&types, &lines] (const auto& sum, const auto& letter) {
        const auto priority = getPriority(letter);
        const auto prioritySum = types[priority - 1] / (lines.size() - 1) * priority;
        types[priority - 1] = 0;
        return prioritySum + sum;
    });
}

auto main() -> int {
    const auto lines = file::getLines("input.txt");

    const auto partOne = std::accumulate(lines.begin(), lines.end(), 0, [] (const auto& sum, const auto& line) {
        const auto middleIterator = line.begin() + line.length() / 2;
        return sum + findMatchingTypesIn({ { line.begin(), middleIterator }, { middleIterator, line.end() } });
    });

    auto partTwo = 0;
    for (std::size_t index = 0; index < lines.size(); index += 3) {
        partTwo += findMatchingTypesIn({ lines[index], lines[index + 1], lines[index + 2] });
    }

    std::cout << "Part 1: " << partOne << '\n' << "Part 2: " << partTwo;
    return 0;
}