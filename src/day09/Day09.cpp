#include "file_utils.h"
#include "string_utils.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <charconv>
#include <set>

struct Knot {
    int x { 0 };
    int y { 0 };
};

void updateDirection(auto& a, auto& b, const auto diff, const auto comp, const auto movement) {
    a -= (diff == 1) * comp;
    a += (diff == -1) * comp;
    b += comp * movement;
}

auto moveLong(std::vector<std::string>& moves, std::size_t length) -> size_t {
    std::vector<Knot> rope { length };
    std::set<std::pair<int, int>> visited {{ 0, 0 }};

    for (const auto& move : moves) {
        const auto split = string::splitString(move, ' ');
        std::size_t distance;
        std::from_chars(split.back().begin(), split.back().end(), distance);

        for (size_t step = 0; step < distance; ++step) {
            rope.front().y += split.front() == "U";
            rope.front().y -= split.front() == "D";
            rope.front().x -= split.front() == "L";
            rope.front().x += split.front() == "R";

            for (size_t i = 1; i < length; ++i) {
                const auto x = rope[i - 1].x;
                const auto y = rope[i - 1].y;
                const auto tx = rope[i].x;
                const auto ty = rope[i].y;

                updateDirection(rope[i].y, rope[i].x, ty - y, tx - x == 2, -1);
                updateDirection(rope[i].y, rope[i].x, ty - y, tx - x == -2, 1);
                updateDirection(rope[i].x, rope[i].y, tx - x, ty - y == 2, -1);
                updateDirection(rope[i].x, rope[i].y, tx - x, ty - y == -2, 1);
            }
            visited.insert({ rope.back().x, rope.back().y });
        }
    }
    return visited.size();
}

auto main() -> int {
    auto moves = file::getLines("input.txt");

    const auto partOne = moveLong(moves, 2);
    const auto partTwo = moveLong(moves, 10);

    std::cout << "part 1: " << partOne << "\npart 2: " << partTwo;
    return 0;
}