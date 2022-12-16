#include "file_utils.h"
#include "string_utils.h"
#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <regex>
#include <set>
#include <list>
#include <map>

struct Valve {
    std::string name;
    long flowRate;
    std::vector<std::string> adjacent;
    std::map<std::string, size_t> costToTarget;
};

const std::regex regex { R"(Valve (\w+) has flow rate=(\d+); tunnels* leads* to valves* (.+))" };

auto parseValves(const std::vector<std::string>& input) -> std::map<std::string, Valve> {
    std::map<std::string, Valve> valves { };
    std::smatch match;

    for (const auto& line: input) {
        std::regex_match(line.begin(), line.end(), match, regex);

        Valve valve {
            .name =  match[1].str(),
            .flowRate = string::toInt(match[2].str())
        };

        const auto splits = string::splitString(match[3].str(), ',');
        for (const auto &split: splits) {
            valve.adjacent.emplace_back(string::trimLeft(split));
        }
        valves.insert( { match[1].str(), valve });
    }
    return valves;
}

// best path plus time to get to and open
auto getBestPathToTarget(std::string valve, std::map<std::string, Valve> valves, std::map<std::string, long> targets, long minute) -> std::pair<std::string, long> {

    // create routes to target for each target
    std::vector<std::pair<std::string, long>> costs { };

    for (const auto [name, cost]: valves[valve].costToTarget) {
        costs.emplace_back(name, cost + 1);
    }

    std::cout << "costs\n";

    for (const auto &item: costs) {
        std::cout <<  item.first << "\n";
    }

    // sort by cost to distance
    // todo: check sorting descending, want to check higest first when filtering
    const auto byCost = [&] (const auto& a, const auto& b) { return valves[a.first].flowRate - a.second > valves[b.first].flowRate - b.second; };
    std::sort(costs.begin(), costs.end(), byCost);

    // filter by minutes available
    const auto findHighest = [&] (const auto& pair) {
        return pair.second < 30 - minute;
    };
    const auto highest = std::ranges::find_if(costs, findHighest);

    // todo: Do we want to check other nodes along the way and work out if stopping would be better?

    // todo: need to handle not found case
    return *highest;
}

auto fillValves(std::map<std::string, Valve>& valves) {
    for (auto& [name, valve]: valves) {
        std::list<std::pair<std::string, long>> heads { };
        heads.emplace_back(valve.name, 0);

        while (!heads.empty()) {
            auto& [head, cost] = heads.front();

            for (auto &adj: valves[head].adjacent) {
                if (adj == name) continue;

                if (!valves[adj].costToTarget.contains(name) || valves[adj].costToTarget[name] > cost + 1) {
                    valves[adj].costToTarget.insert_or_assign(name, cost + 1);
                    heads.emplace_back(adj, cost + 1);
                }
            }
            heads.pop_front();
        }
    }

    for (const auto &valve: valves) {
        std::cout << "valve: " << valve.second.name << "\n";

        for (const auto &[adj, cost]: valve.second.costToTarget) {
            std::cout << adj << " - cost: " << cost << "\n";
        }

        std::cout << "\n";
    }
}

auto partOne(const std::vector<std::string>& input) -> size_t {
    std::map<std::string, Valve> valves = parseValves(input);

     std::string current = "AA";

    std::vector<long> openFlowRates { };
    std::map<std::string, long> targets { };
    for (auto& [name, valve]: valves) {
        if (valve.flowRate != 0) targets.insert( { name, valve.flowRate });
    }

    fillValves(valves);

    std::cout << "after fill \n";
    for (const auto &[name, valve]: valves) {
        std::cout << name << " - " << valve.name << "\n";
    }

    long sum = 0;
    long minute = 0;
    while (minute <= 30) {
        if (!targets.empty()) {
            const auto [bestValve, time] = getBestPathToTarget(current, valves, targets, minute);
            //auto bestValue = "AA";
            //auto time = 1;

            for (const auto &rate: openFlowRates) {
                sum += rate * time;
            }
            minute += time;

            openFlowRates.push_back(valves[bestValve].flowRate);

            std::cout << "after pick \n";
            for (const auto &[name, valve]: valves) {
                std::cout << name << " - " << valve.name << "\n";
            }

            std::cout << "best value: " << bestValve << '\n';
            std::cout << "picked: " << valves[bestValve].name << '\n';

            current = bestValve;

            targets.erase(valves[bestValve].name);
        } else {
            for (const auto &rate: openFlowRates) {
                sum += rate * 1;
                ++minute;
            }
        }
    }
    return sum;
}


auto main() -> int {
    auto values = file::getLines("input.txt");

    const auto partTwo = 0;

    std::cout << "part 1: " << partOne(values) << "\npart 2: " << partTwo;
    return 0;
}