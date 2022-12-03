#include <iostream>
#include <vector>
#include <functional>
#include <array>
#include <numeric>
#include "file_utils.h"

auto findMatchingTypesIn(const std::string_view& line, auto&& onPriority) {
    for (const auto & letter : line) {
        const auto value = static_cast<int>(letter ^ ' ');
        const auto priority = value - 64 - ((value / 91) * 6);
        onPriority(priority);
    }
}

auto findMatchingTypesIn(std::vector<std::string_view>&& lines) -> int {
    std::array<int, 52> array { };
    std::for_each(lines.begin(), lines.end() - 1, [&array, index = 1] (const auto & line) mutable {

        findMatchingTypesIn(line, [&array, &index] (const auto & priority) {
            // todo: Open add one if index is 1 less than current priority
            if (array[priority - 1] == index - 1) {
                array[priority - 1] += 1;
            }
        });

//        for (const auto & letter : line) {
//            const auto value = static_cast<int>(letter ^ ' ');
//            const auto priority = value - 64 - ((value / 91) * 6);
//
//            // todo: only increment if previous had value
//            if (array[priority - 1] == index - 1) {
//                array[priority - 1] += 1;
//            }
//        }
        ++index;
    });

    auto sum = 0;
    findMatchingTypesIn(lines.back(), [&array, &sum, &lines] (const auto & priority) mutable {
        sum += (array[priority - 1] / (lines.size() - 1)) * priority;
        array[priority - 1] = 0;
    });
//
//    for(const auto & letter : lines.back()) {
//        const auto value = static_cast<int>(letter ^ ' ');
//        const auto priority = value - 64 - ((value / 91) * 6);
//        sum += (array[priority - 1] / (lines.size() - 1)) * priority;
//        array[priority - 1] = 0;
//    }

    return sum;
}

auto main() -> int {
    const auto lines = file::getLines("input.txt");

    const auto partOne = std::accumulate(lines.begin(), lines.end(), 0, [] (const auto& sum, const auto& line) {
        return sum + findMatchingTypesIn(std::vector<std::string_view> {
            { line.begin(), line.begin() + line.length() / 2 },
            { line.begin() + line.length() / 2, line.end() }
        });
    });

    auto partTwo = 0;
    for (int i = 0; i < lines.size(); i = i + 3) {
        partTwo += findMatchingTypesIn(std::vector<std::string_view> { lines[i], lines[i + 1], lines[i + 2] });
    }

    std::cout << "Part 1: " << partOne << '\n' << "Part 2: " << partTwo;

//    auto sum = 0;
//    for(const auto & line : lines) {
//        auto array = std::array<int, 52> { };
//
//        // todo: Could alter to be a function that takes a vector or array of input strings?
//        // todo: or maybe a set of string views?
//        // todo: and then the array stores the number up to size - 1 and checks if it == size - 1
//        // in that case need to do first loop for all items and last loop for last item
//
//        // todo: Could do some sort of running index or over half check here
//        const auto lineHalf = line.begin() + (line.length() / 2);
//        std::for_each(line.begin(), lineHalf, [&array] (const auto & letter) {
//            const auto value = static_cast<int>(letter ^ ' ');
//            const auto priority = value - 64 - ((value / 91) * 6);
//            array[priority - 1] = 1;
//        });
//
//        std::for_each(lineHalf, line.end(), [&array, &sum] (const auto & letter) {
//            const auto value = static_cast<int>(letter ^ ' ');
//            const auto priority = value - 64 - ((value / 91) * 6);
//            sum += array[priority - 1] * priority;
//            array[priority - 1] = 0;
//        });
//    }
//
//    std::cout << "Part 1: " << sum << '\n' << "Part 2: " << 2;
    return 0;
}