#include "Day14.h"
#include "string_utils.h"
#include <vector>
#include <ranges>
#include <regex>

class Map {
public:
    enum Tile { AIR = 0, ROCK = 1, SAND = 2 };

    explicit Map(size_t width) : width(width) { }

    auto operator[](const size_t y, const size_t x) -> Tile& { return grid[y][x]; }

    [[nodiscard]]
    auto getHeight() const -> size_t { return grid.size(); }

    auto resizeMap(std::size_t y) {
        height = ((y + 1 > height) * (y + 1)) + (height * (y + 1 <= height));
        grid.insert(grid.end(), height - grid.size(), std::vector<Tile> { width, Tile::AIR });
    }

    auto insertWall(std::pair<size_t, size_t> start, std::pair<size_t, size_t> end) {
        const auto maxX = std::max(start.first, end.first);
        const auto maxY = std::max(start.second, end.second);
        const auto minX = std::min(start.first, end.first);
        const auto minY = std::min(start.second, end.second);
        resizeMap(maxY);

        for (auto index = minX; index <= maxX; ++index) {
            operator[](maxY, index) = Tile::ROCK;
        }

        for (auto index = minY; index <= maxY; ++index) {
            operator[](index, maxX) = Tile::ROCK;
        }
    }

private:
    std::vector<std::vector<Tile>> grid { };
    size_t height = 0;
    size_t width = 0;
};

const std::regex regex { R"((\d+,\d+))" };

auto parseCoords(const std::string& row) -> std::vector<std::pair<size_t, size_t>> {
    std::vector<std::pair<size_t, size_t>> nodes { };
    std::smatch match;
    auto start = row.begin();
    while (std::regex_search(start, row.end(), match, regex)) {
        const auto coords = string::splitString(match[1].str(), ',');
        start = match.suffix().first;
        nodes.emplace_back(string::toInt(coords.front()), string::toInt(coords.back()));
    }
    return nodes;
}

auto buildMap(const std::vector<std::string>& walls) -> Map {
    Map map { 1000 };
    for (const auto &wall: walls) {
        const auto nodes = parseCoords( wall);
        for (int index = 0; index < nodes.size() - 1; ++index) {
            map.insertWall(nodes[index], nodes[index + 1]);
        }
    }
    return map;
}

auto countSand(Map map) -> size_t {
    auto finished = false;
    auto count = 0;
    auto currentSand = std::pair { 500, 0 };
    while (!finished) {
        if (map[currentSand.second + 1, currentSand.first] == Map::Tile::AIR) {
            ++currentSand.second;
        }
        else if (map[currentSand.second + 1, currentSand.first -1] == Map::Tile::AIR) {
            ++currentSand.second;
            --currentSand.first;
        }
        else if (map[currentSand.second + 1, currentSand.first + 1] == Map::Tile::AIR) {
            ++currentSand.second;
            ++currentSand.first;
        }
        else {
            map[currentSand.second, currentSand.first] = Map::Tile::SAND;
            ++count;
            finished = (finished + (currentSand.first == 500 && currentSand.second == 0)) > 0;
            currentSand = std::pair { 500, 0 };
        }

        finished = (finished + (currentSand.second >= map.getHeight() - 1)) > 0;
    }
    return count;
}

auto Day14::partOne(const std::vector<std::string>& walls) -> size_t {
    auto map = buildMap(walls);
    return countSand(map);
}

auto Day14::partTwo(const std::vector<std::string>& walls) -> size_t {
    auto map = buildMap(walls);
    std::pair<size_t, size_t> start { 0, map.getHeight() + 1 };
    std::pair<size_t, size_t> end { 999, map.getHeight() + 1 };
    map.insertWall(start, end);
    return countSand(map);
}