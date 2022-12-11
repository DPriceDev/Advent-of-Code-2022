#include "Day11.h"
#include "string_utils.h"
#include <iostream>
#include <algorithm>
#include <charconv>
#include <list>
#include <functional>
#include <numeric>

struct Monkey {
    std::list<std::size_t> items;
    std::function<std::size_t (std::size_t)> operation;
    std::size_t testDivisor;
    std::size_t trueMonkeyIndex;
    std::size_t falseMonkeyIndex;
    std::size_t inspectCount = 0;
};

auto getValue(const auto& start, const auto& end) -> size_t {
    std::size_t value;
    const auto view = std::string_view { start, end };
    std::from_chars(view.begin(), view.end(), value);
    return value;
}

auto parseMonkey(const std::span<std::string>& lines) -> Monkey {
    Monkey monkey {
        .testDivisor = getValue(lines[3].begin() + 21, lines[3].end()),
        .trueMonkeyIndex = getValue(lines[4].begin() + 29, lines[4].end()),
        .falseMonkeyIndex = getValue(lines[5].begin() + 30, lines[5].end())
    };

    std::string_view view { lines[1].begin() + 17, lines[1].end() };
    const auto items = string::splitString(view, ',');
    for (const auto item : items) {
        size_t value;
        std::from_chars(item.begin() + 1, item.end(), value);
        monkey.items.push_back(value);
    }

    view = std::string_view { lines[2].begin() + 25, lines[2].end() };
    const size_t value = getValue(view.begin(), view.end());
    if (lines[2][23] == '*') {
        if (view != "old") {
            monkey.operation = [value] (const size_t old) { return old * value; };
        } else {
            monkey.operation = [] (const size_t old) { return old * old; };
        }
    } else {
        monkey.operation = [value] (const size_t old) { return old + value; };
    }

    return monkey;
}

auto parseMonkeys(std::vector<std::string>& lines) -> std::vector<Monkey> {
    std::vector<Monkey> monkeys { };
    for (long i = 0; i < lines.size(); i += 7) {
        const std::span<std::string> monkeyLines { lines.begin() + i, lines.begin() + i + 7 };
        const auto monkey = parseMonkey(monkeyLines);
        monkeys.push_back(monkey);
    }
    return monkeys;
}

auto chaseMonkeys(std::vector<Monkey>& monkeys, const std::size_t rounds, const auto& worryAdjuster) -> std::size_t {
    for (std::size_t round = 0; round < rounds; ++round) {
        for (auto& monkey: monkeys) {
            for (const auto &item: monkey.items) {
                const auto inspected = monkey.operation(item);
                const auto adjusted = worryAdjuster(inspected);

                const auto isDivisible = adjusted % monkey.testDivisor == 0;
                const auto index = (isDivisible) ? monkey.trueMonkeyIndex : monkey.falseMonkeyIndex;

                monkeys[index].items.push_back(adjusted);
                monkey.inspectCount += 1;
            }
            monkey.items.clear();
        }
    }

    std::vector<std::size_t> counts { monkeys.size() };
    const auto toInspectCount = [](const auto &monkey) { return monkey.inspectCount; };
    std::transform(monkeys.begin(), monkeys.end(), std::back_inserter(counts), toInspectCount);
    std::sort(counts.begin(), counts.end());
    return *counts.rbegin() * *(counts.rbegin() + 1);
}

auto Day11::partOne(std::vector<std::string>& lines) -> size_t {
    auto monkeys = parseMonkeys(lines);
    const auto divThree = [] (const auto worry) { return worry / 3; };
    return chaseMonkeys(monkeys, 20, divThree);
}

auto Day11::partTwo(std::vector<std::string>& lines) -> size_t {
    auto monkeys = parseMonkeys(lines);

    const auto toDivisor = [] (const auto& a) { return a.testDivisor; };
    const auto view = monkeys | std::views::transform(toDivisor);

    const auto commonDivisor = std::accumulate(view.begin(), view.end(), 1, std::multiplies());
    const auto byCommonDivisor = [&commonDivisor] (const auto worry) { return worry % commonDivisor; };
    return chaseMonkeys(monkeys, 10000, byCommonDivisor);
}

//auto main() -> int {
//    auto lines = file::getLines("input.txt");
//    std::cout << "part 1: " << Day11::partOne(lines) << "\npart 2: " << Day11::partTwo(lines);
//    return 0;
//}