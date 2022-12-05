#include <iostream>
#include "file_utils.h"
#include <regex>
#include <vector>
#include <span>

const std::regex regex { R"(move (\d+) from (\d+) to (\d))" };

auto parseStacks(const std::span<std::basic_string<char>>&& lines) -> std::vector<std::vector<char>> {
    std::vector<std::vector<char>> stacks { (lines.rbegin()->size() / 4) + 2 };
    std::for_each(lines.rbegin(), lines.rend(), [&stacks] (const auto& line) {
        for (int index = 0; index < line.length(); index += 4) {
            if (line[index] != ' ') stacks[index / 4].emplace_back(line[index + 1]);
        }
    });
    stacks.pop_back();
    return stacks;
}

auto sortStacks(std::vector<std::vector<char>>& stacks, const std::span<std::basic_string<char>>&& commands, const bool keepMoveOrder) {
    std::smatch match;
    for (const auto & command: commands) {
        std::regex_match(command.begin(), command.end(), match, regex);
        const auto count = stoi(match[1]);
        const auto from = stoi(match[2]) - 1;
        const auto to = stoi(match[3]) - 1;

        if (keepMoveOrder) {
            std::copy(stacks[from].end() - count, stacks[from].end(), std::back_inserter(stacks[to]));
        } else {
            std::copy(stacks[from].rbegin(), stacks[from].rbegin() + count, std::back_inserter(stacks[to]));
        }

        for (int index = 0; index < count; ++index) { stacks[from].pop_back(); }
    }
}

auto main() -> int {
    auto lines = file::getLines("input.txt");
    const auto divider = std::find(lines.begin(), lines.end(), "");

    auto stacks = parseStacks({ lines.begin(), divider });
    std::vector<std::vector<char>> partTwoStacks;
    std::copy(stacks.begin(), stacks.end(), std::back_inserter(partTwoStacks));

    sortStacks(stacks, { divider + 1, lines.end() }, false);
    std::cout << "Part 1: ";
    for (const auto & stack : stacks) { std::cout << stack.back(); }

    sortStacks(partTwoStacks, { divider + 1, lines.end() }, true);
    std::cout << "\nPart 2: ";
    for (const auto & stack : partTwoStacks) { std::cout << stack.back(); }

    return 0;
}