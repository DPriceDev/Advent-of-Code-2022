#include "file_utils.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <set>

struct Knot {
    int x { 0 };
    int y { 0 };
};

auto moveLong(std::vector<std::string>& moves, std::size_t length) -> size_t {
    std::vector<Knot> rope { length };
    // todo: replace with vector array?
    std::set<std::pair<int, int>> visited {{ 0, 0 }};

    for (const auto& move : moves) {
        // todo: shrink?
        std::stringstream stream { move };
        char direction;
        int distance;
        stream >> direction;
        stream >> distance;

        for (int step = 0; step < distance; ++step) {
            rope.front().y += direction == 'U';
            rope.front().y -= direction == 'D';
            rope.front().x -= direction == 'L';
            rope.front().x += direction == 'R';

            for (int i = 1; i < length; ++i) {
                auto x = rope[i - 1].x;
                auto y = rope[i - 1].y;
                auto tx = rope[i].x;
                auto ty = rope[i].y;

                // todo: can this be rotated?
                const auto txx = tx - x == 2;
                rope[i].y -= (ty - y == 1) * txx;
                rope[i].y += (ty - y == -1) * txx;

                rope[i].x -= txx;

                const auto ntxx = tx - x == -2;
                rope[i].y -= (ty - y == 1) * ntxx;
                rope[i].y += (ty - y == -1) * ntxx;

                rope[i].x += ntxx;

                const auto tyy = ty - y == 2;
                rope[i].x -= (tx - x == 1) * tyy;
                rope[i].x += (tx - x == -1) * tyy;
                rope[i].y -= tyy;

                const auto ntyy = ty - y == -2;
                rope[i].x -= (tx - x == 1) * ntyy;
                rope[i].x += (tx - x == -1) * ntyy;

                rope[i].y += ntyy;
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