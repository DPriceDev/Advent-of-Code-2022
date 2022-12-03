#include <iostream>
#include <vector>
#include <functional>
#include <array>
#include "file_utils.h"

auto getPoints(const std::vector<std::string>& lines, const auto& getScore) -> int {
    constexpr auto points = std::array<int, 5> { 6, 0, 3, 6, 0 };
    constexpr auto moves = std::array<int, 5> { 3, 1, 2, 3, 1 };

    auto score = 0;
    for(const auto& line: lines) {
        const auto theirMove = static_cast<int>(line.front()) - 64;
        const auto ourMove = getScore(theirMove, static_cast<int>(line.back()) - 87);
        score += moves[ourMove] + points[ourMove - theirMove + 2];
    }
    return score;
}

auto main() -> int {
    const auto lines = file::getLines("input.txt");

    const auto partOne = getPoints(lines, [] (const int& theirs, const int& ours) { return ours; });
    const auto partTwo = getPoints(lines, [] (const int& theirs, const int& ours) { return theirs + ours - 2; });

    std::cout << "Part 1: " << partOne << '\n' << "Part 2: " << partTwo;
    return 0;
}