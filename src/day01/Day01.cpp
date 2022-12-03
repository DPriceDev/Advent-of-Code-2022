#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include "file_utils.h"

auto parseTotalCalories(const std::vector<std::string>& lines) -> std::vector<int> {
    std::vector<int> calories { 0 };
    for(const auto & line : lines) {
        if (line.empty()) calories.push_back(0); else calories.back() += stoi(line);
    }
    return calories;
}

auto main() -> int {
    const auto lines = file::getLines("input.txt");
    auto totalCalories = parseTotalCalories(lines);

    std::sort(totalCalories.begin(), totalCalories.end());
    const auto topThreeCalories = std::reduce(totalCalories.rbegin(), totalCalories.rbegin() + 3);

    std::cout << "Part 1: " << totalCalories.back() << " Part 2: " << topThreeCalories << '\n';
    return 0;
}