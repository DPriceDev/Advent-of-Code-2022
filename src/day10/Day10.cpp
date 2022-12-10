#include "file_utils.h"
#include <iostream>
#include <vector>
#include <charconv>

auto parse(const std::vector<std::string>& lines, const auto&& onAction) {
    auto cycle = 0;
    auto x = 1;
    for (const auto& line : lines) {
        onAction(cycle, x);
        if (line.starts_with("addx")) {
            int value;
            std::from_chars(line.data() + 5, line.data() + line.size(), value);
            onAction(cycle, x);
            x += value;
        }
    }
}

auto partOne(const std::vector<std::string>& lines) -> int {
    auto multiple = 0;
    parse(lines, [&] (auto& cycle, const auto x) {
        ++cycle;
        multiple += (x * cycle) * ((cycle - 20) % 40 == 0);
    });
    return multiple;
}

auto partTwo(const std::vector<std::string>& lines) {
    parse(lines, [] (auto& cycle, const auto x) {
        if (cycle % 40 == 0) std::cout << "\n";
        const auto current = cycle - (40 * (cycle / 40));
        std::cout << ((x >= current - 1 && x <= current + 1) ? '#' : ' ');
        ++cycle;
    });
}

auto main() -> int {
    auto lines = file::getLines("input.txt");
    const auto one = partOne(lines);
    std::cout << "\npart 1: " << one << "\npart 2:";
    partTwo(lines);
    return 0;
}