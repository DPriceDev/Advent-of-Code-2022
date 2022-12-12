#include "Day12.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <list>

enum Type {
    START,
    END,
    TILE
};

struct Node {
    size_t height;
    bool visited = false;
    Type type = Type::TILE;
    size_t score = 10000;
};

struct Map {
    std::vector<std::vector<Node>> map;
    std::pair<size_t, size_t> start;
    std::pair<size_t, size_t> target;
};

auto buildMap(const std::vector<std::string>& lines, std::pair<size_t, size_t>* start) -> Map {
    Map map;

    size_t y = 0;
    const auto toNodeRow = [&] (const auto& row) {
        std::vector<Node> newRow { };
        size_t x = 0;
        const auto toNode = [&] (const auto value) {
            Type type = Type::TILE;
            auto height = static_cast<size_t>(value);
            size_t score = 9999;

            if (start != nullptr && y == start->second && x == start->first) {
                score = 0;
            }

            if (value == 'S') {
                map.start = std::pair<size_t, size_t> { x, y };
                type = Type::START;
                height = static_cast<size_t>('a');
                if (start == nullptr) {
                    score = 0;
                }

            }
            if (value == 'E') {
                map.target = std::pair<size_t, size_t> { x, y };
                type = Type::END;
                height = static_cast<size_t>('z');
            }
            ++x;

            return Node { .height = height, .type = type, .score = score };
        };
        std::transform(row.begin(), row.end(), std::back_inserter(newRow), toNode);
        ++y;
        return newRow;
    };
    std::transform(lines.begin(), lines.end(), std::back_inserter(map.map), toNodeRow);
    return map;
}

auto getSurroundingNodes(Map& map, size_t x, size_t y) -> std::vector<std::pair<size_t, size_t>> {
    std::vector<std::pair<size_t, size_t>> nodes;
    if (y > 0) nodes.emplace_back( x, y - 1);
    if (x > 0) nodes.emplace_back( x - 1, y);
    if (y < map.map.size() - 1) nodes.emplace_back( x, y + 1);
    if (x < map.map.front().size() - 1) nodes.emplace_back(x + 1, y);
    return nodes;
}

auto stepsToTop(Map map) -> size_t {

    std::list<std::pair<size_t, size_t>> nodes { map.start };
    auto found = false;
    while (!nodes.empty() && !found) {
        const auto currentCoord = nodes.front();
        const auto currentNode = map.map[currentCoord.second][currentCoord.first];

        auto others = getSurroundingNodes(map, currentCoord.first, currentCoord.second);

        for (const auto& coord: others) {
            auto& node = map.map[coord.second][coord.first];

            auto diff = static_cast<long long>(node.height) - static_cast<long long>(currentNode.height);
            if (diff > 1) {
                continue;
            }

            if (currentNode.score + 1 < node.score) {
                node.score = currentNode.score + 1;
                nodes.push_back(coord);
            }
        }

        nodes.pop_front();
    }

    const auto node = map.map[map.target.second][map.target.first];
    return node.score;
}

auto getLowestStartingHeight(const std::vector<std::string>& lines) -> size_t {
    size_t shortest = 999;

    auto y = 0;
    for (const auto &line: lines) {

        auto x = 0;
        for (const char point: line) {
            if (point == 'a') {
                auto start = std::pair<size_t, size_t> { x, y };
                auto map = buildMap(lines, &start);
                map.start = std::pair<size_t, size_t> { x, y };

                size_t result = stepsToTop(map);
                if (result < shortest) shortest = result;
            }
            x++;
        }

        y++;
    }

    return shortest;
}

auto Day12::partOne(const std::vector<std::string>& lines) -> size_t {
    const auto map = buildMap(lines, nullptr);
    return stepsToTop(map);
}

auto Day12::partTwo(const std::vector<std::string>& lines) -> size_t {
    return getLowestStartingHeight(lines);
}