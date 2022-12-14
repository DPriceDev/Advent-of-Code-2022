#include "file_utils.h"
#include "string_utils.h"
#include <iostream>
#include <vector>
#include <ranges>
#include <regex>

const std::regex regex { R"((\d+,\d+))" };

enum Tile {
    AIR = 0,
    ROCK = 1,
    SAND = 2,
};

// todo: multi dimension operator
struct Map {
    std::vector<std::vector<Tile>> grid { 500 };
    size_t highest = 0;

    // todo: would be good to dynamically resize this grid

    auto resizeMap(std::size_t x, std::size_t y) {
        grid.resize(500);
        for (auto& row: grid) {
            row.resize(10000);
        }

        if (y + 1 >= grid.size()) {
            grid.resize(y + 1);
        }

        if (x + 1 >= grid.front().size()) {
            for (auto& row: grid) {
                row.resize(x + 1);
            }
        }
    }

    auto insertWall(std::pair<size_t, size_t> start, std::pair<size_t, size_t> end) {
        const auto maxX = std::max(start.first, end.first);
        const auto maxY = std::max(start.second, end.second);
        const auto minX = std::min(start.first, end.first);
        const auto minY = std::min(start.second, end.second);

        if (maxY > highest) highest = maxY;

       // print();
        resizeMap(maxX, maxY);

        for (size_t index = minX; index <= maxX; ++index) {
            auto la = grid[maxY].size();
            grid[maxY][index] = Tile::ROCK;
            auto lb = grid[maxY].size();
            auto test = 2;
        }

        for (size_t index = minY; index <= maxY; ++index) {
            auto la = grid[index].size();
            grid[index][maxX] = Tile::ROCK;
            auto lb = grid[index].size();
            auto test = 2;
        }
    }

    void print() {
        for (const auto &row: grid) {
            for (const auto &tile: row) {
                if (tile == Tile::ROCK) std::cout << '#';
                if (tile == Tile::SAND) std::cout << 'o';
                if (tile == Tile::AIR) std::cout << '.';
            }
            std::cout << "    " << row.size() << '\n';
        }
        std::cout << '\n';
    }
};

auto buildMap(const std::vector<std::string>& walls) -> Map {
    Map map;

    std::smatch match;
    std::vector<std::pair<size_t, size_t>> nodes { };
    for (const auto &wall: walls) {
        auto start = wall.begin();
        while (std::regex_search(start, wall.end(), match, regex)) {
            const auto coords = string::splitString(match[1].str(), ',');
            start = match.suffix().first;
            nodes.emplace_back(string::toInt(coords.front()), string::toInt(coords.back()));
        }

        for (int index = 0; index < nodes.size() - 1; ++index) {
            //std::cout << "inserting " << nodes[index].first << " " << nodes[index].second << " to " << nodes[index + 1].first << " " << nodes[index + 1].second << '\n';
            map.insertWall(nodes[index], nodes[index + 1]);
        }
        nodes.clear();
    }

    return map;
}

auto countSand(Map map) -> size_t {

    auto finished = false;
    auto count = 0;
    auto currentSand = std::pair<size_t, size_t> { 500, 0 };
    while (!finished) {

        if (map.grid[currentSand.second + 1][currentSand.first] == AIR) {
            currentSand.second = currentSand.second + 1;
        }
        else if (map.grid[currentSand.second + 1][currentSand.first -1] == AIR) {
            currentSand.second = currentSand.second + 1;
            currentSand.first = currentSand.first - 1;
        }
        else if (map.grid[currentSand.second + 1][currentSand.first + 1] == AIR) {
            currentSand.second = currentSand.second + 1;
            currentSand.first = currentSand.first + 1;
        }
        else {
            map.grid[currentSand.second][currentSand.first] = SAND;
            currentSand = std::pair<size_t, size_t> { 500, 0 };
            count++;
           // map.print();
        }

        if (currentSand.second >= map.grid.size() - 1) {
            finished = true;
        }
    }

    map.print();
    return count;
}

auto countAllSand(Map map) -> size_t {

    auto finished = false;
    auto count = 0;
    auto currentSand = std::pair<size_t, size_t> { 500, 0 };
    while (!finished) {

        auto height = map.highest + 2 - 1;
        auto atBottom = currentSand.second >= height;

        if (atBottom) {
            map.grid[currentSand.second][currentSand.first] = SAND;
            currentSand = std::pair<size_t, size_t> { 500, 0 };
            count++;
        }
        else if (map.grid[currentSand.second + 1][currentSand.first] == AIR) {
            currentSand.second = currentSand.second + 1;
        }
        else if (map.grid[currentSand.second + 1][currentSand.first -1] == AIR) {
            currentSand.second = currentSand.second + 1;
            currentSand.first = currentSand.first - 1;
        }
        else if (map.grid[currentSand.second + 1][currentSand.first + 1] == AIR) {
            currentSand.second = currentSand.second + 1;
            currentSand.first = currentSand.first + 1;
        }
        else {
            map.grid[currentSand.second][currentSand.first] = SAND;
            count++;

            if (currentSand.first == 500 && currentSand.second == 0) {
                finished = true;
            }
            currentSand = std::pair<size_t, size_t> { 500, 0 };
        }
    }

    //map.print();
    return count;
}

auto main() -> int {
    auto walls = file::getLines("input.txt");

    auto map = buildMap(walls);

    const auto partOne = countSand(map);
    const auto partTwo = countAllSand(map);

    std::cout << "part 1: " << partOne << "\npart 2: " << partTwo;
    return 0;
}