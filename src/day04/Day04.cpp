#include <iostream>
#include "file_utils.h"
#include <tuple>
#include <regex>

const std::regex regex { R"((\d+)-(\d+),(\d+)-(\d+))" };

auto parsePairs(const std::string& line) -> std::tuple<int, int, int, int> {
    std::smatch match;
    std::regex_match(line.begin(), line.end(), match, regex);
    return std::make_tuple(stoi(match[1]), stoi(match[2]), stoi(match[3]), stoi(match[4]));
}

auto main() -> int {
    const auto lines = file::getLines("input.txt");

    auto partOne = 0;
    for (const auto & line : lines) {
        auto [a1, a2, b1, b2] = parsePairs(line);
        if ((a1 >= b1 && a1 <= b2 && a2 >= b1 && a2 <= b2) || (b1 >= a1 && b1 <= a2 && b2 >= a1 && b2 <= a2)) ++partOne;
    }

    auto partTwo = 0;
    for (const auto & line : lines) {
        auto [a1, a2, b1, b2] = parsePairs(line);
        if (a1 >= b1 && a1 <= b2 || a2 >= b1 && a2 <= b2) ++partTwo;
    }

    std::cout << "Part 1: " << partOne << '\n' << "Part 2: " << partTwo;
    return 0;
}