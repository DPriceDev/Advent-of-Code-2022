#include "file_utils.h"
#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <map>
#include <sstream>
#include <set>

auto moveHead(std::vector<std::string>& moves) -> size_t {

    auto x { 0 };
    auto y { 0 };

    auto tx { 0 };
    auto ty { 0 };

    std::set<std::pair<int, int>> visited {{ tx, ty }};

    for (const auto& move : moves) {
        std::stringstream stream { move };
        char direction;
        int distance;
        stream >> direction;
        stream >> distance;

        for (int step = 0; step < distance; ++step) {
            // move head
            if (direction == 'U') y += 1;
            if (direction == 'D') y -= 1;
            if (direction == 'L') x -= 1;
            if (direction == 'R') x += 1;

            // move tail
            if (tx - x == 2) {
                if (ty - y == 1) ty -= 1;
                if (ty - y == -1) ty += 1;
                tx -= 1;
            }
            if (tx - x == -2) {
                auto test = ty - y;
                if (ty - y == 1) ty -= 1;
                if (ty - y == -1) ty += 1;
                tx += 1;
            }
            if (ty - y == 2) {
                if (tx - x == 1) tx -= 1;
                if (tx - x == -1) tx += 1;
                ty -= 1;
            }
            if (ty - y == -2) {
                if (tx - x == 1) tx -= 1;
                if (tx - x == -1) tx += 1;
                ty += 1;
            }

            visited.insert({ tx, ty });


//            for (int ay = 6; ay >= 0; --ay) {
//                for (int ax = 0; ax < 6; ++ax) {
//                    if (x == ax && y == ay) {
//                        std::cout << "H";
//                        continue;
//                    }
//
//                    if (tx == ax && ty == ay) {
//                        std::cout << "T";
//                        continue;
//                    }
//                    std::cout << ".";
//
//                }
//                std::cout << "\n";
//            }
//            std::cout << "\n";
//
//            std::cout << x << " " << y << " " << tx << " " << ty << "\n";
        }
    }
    return visited.size();
}

struct Knot {
    int x { 0 };
    int y { 0 };
};

auto moveLong(std::vector<std::string>& moves) -> size_t {

    std::array<Knot, 10> rope { };

    std::set<std::pair<int, int>> visited {{ 0, 0 }};

    for (const auto& move : moves) {
        std::stringstream stream { move };
        char direction;
        int distance;
        stream >> direction;
        stream >> distance;

        for (int step = 0; step < distance; ++step) {
            // move head
            if (direction == 'U') rope[0].y += 1;
            if (direction == 'D') rope[0].y -= 1;
            if (direction == 'L') rope[0].x -= 1;
            if (direction == 'R') rope[0].x += 1;

            for (int i = 1; i < rope.size(); ++i) {
                auto x = rope[i - 1].x;
                auto y = rope[i - 1].y;
                auto tx = rope[i].x;
                auto ty = rope[i].y;

                // move tail
                if (tx - x == 2) {
                    if (ty - y == 1) rope[i].y -= 1;
                    if (ty - y == -1) rope[i].y += 1;
                    rope[i].x -= 1;
                }
                if (tx - x == -2) {
                    if (ty - y == 1) rope[i].y -= 1;
                    if (ty - y == -1) rope[i].y += 1;
                    rope[i].x += 1;
                }
                if (ty - y == 2) {
                    if (tx - x == 1) rope[i].x -= 1;
                    if (tx - x == -1) rope[i].x += 1;
                    rope[i].y -= 1;
                }
                if (ty - y == -2) {
                    if (tx - x == 1) rope[i].x -= 1;
                    if (tx - x == -1) rope[i].x += 1;
                    rope[i].y += 1;
                }

                if (i == 9) {
                    visited.insert({ rope[i].x, rope[i].y });
                }
            }

            for (int ay = 20; ay >= 0; --ay) {
                for (int ax = 0; ax < 20; ++ax) {

                    auto index = 0;
                    auto found = false;
                    for (const auto& knot : rope) {
                        if (knot.x == ax && knot.y == ay && !found) {
                            std::cout << index << "";
                            found = true;
                            //continue;
                        }
                        index++;
                    }

                    if (!found) {
                        std::cout << ".";
                    }

                }
                std::cout << "\n";

           // std::cout << "\n";

           // std::cout << x << " " << y << " " << tx << " " << ty << "\n";
            }
             std::cout << "\n";
        }
    }
    return visited.size();
}

auto main() -> int {
    auto moves = file::getLines("input.txt");

    const auto partOne = moveHead(moves);
    const auto partTwo = moveLong(moves);

    std::cout << "part 1: " << partOne << "\npart 2: " << partTwo;
    return 0;
}