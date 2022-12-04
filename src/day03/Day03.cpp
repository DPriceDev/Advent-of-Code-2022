#include <iostream>
#include <vector>
#include <array>
#include <chrono>
#include "file_utils.h"

auto getPriority(const char& letter) -> int {
    const auto asciiValue = static_cast<int>(letter ^ ' ');
    return asciiValue - 64 - ((asciiValue / 91) * 6);
}

constexpr auto findMatchingTypes(std::vector<std::string_view>&& lines) -> int {
    std::array<int, 52> types { };

    for (std::size_t index = 0; index < lines.size() - 1; ++index) {
        for (const auto& letter : lines[index]) {
            const auto priority = getPriority(letter);
            types[priority - 1] += types[priority - 1] == index;
        }
    }

    auto sum = 0;
    for(const auto& letter: lines.back()) {
        const auto priority = getPriority(letter);
        sum += types[priority - 1] / (lines.size() - 1) * priority;
        types[priority - 1] = 0;
    }
    return sum;
}

auto main() -> int {
    const auto lines = file::getLines("input.txt");

    auto partOne = 0;
    for (const auto  & line : lines) {
        const auto middleIterator = line.begin() + line.length() / 2;
        partOne += findMatchingTypes({ {line.begin(),   middleIterator}, {middleIterator, line.end()} });
    }

    auto partTwo = 0;
    for (std::size_t index = 0; index < lines.size(); index += 3) {
        partTwo += findMatchingTypes({lines[index], lines[index + 1], lines[index + 2]});
    }

    std::cout << "Part 1: " << partOne << '\n' << "Part 2: " << partTwo;
    return 0;
}