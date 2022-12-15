#include "file_utils.h"
#include "string_utils.h"
#include <iostream>
#include <vector>
#include <ranges>
#include <regex>
#include <set>

struct Position {
    long x;
    long y;
};

struct Sensor {
    Position position;
    Position nearestBeacon;
};

const std::regex sensorRegex {
    R"(Sensor at x=(-*\d+), y=(-*\d+): closest beacon is at x=(-*\d+), y=(-*\d+))"
};

auto parseSensor(const std::string& input) -> Sensor {
    std::smatch match;
    std::regex_match(input.begin(), input.end(), match, sensorRegex);
    return Sensor {
        .position = Position { string::toInt(match[1].str()), string::toInt(match[2].str()) },
        .nearestBeacon = Position { string::toInt(match[3].str()), string::toInt(match[4].str()) }
    };
}

// too high 6180329
// exactly 6078701
// too low 5787756
// too low 5787756
// too low 5848973

struct Range {
    long start;
    long end;
    bool isValid = true;

    [[nodiscard]]
    auto length() const -> size_t {
        return (isValid) ? (end - start) + 1 : 0;
    };

    void subtract(Range &other) {
        if (start >= other.start && end <= other.end) {
            isValid = false;
        }
        else if (other.start >= start && other.end <= end) {
            other.isValid = false;
        }
        else if (isValid) {
            if (start >= other.start && start <= other.end) {
                start = other.end + 1;
            }
            if (end >= other.start && end <= other.end) {
                end = other.start - 1;
            }
        }
    }
};

auto partOne(std::vector<std::string>& sensorsInput) -> size_t {
    const auto rowToCheck = 2000000;
    std::set<long> positions { };

    std::vector<Range> ranges { };

    std::vector<Sensor> sensors { };
    std::vector<Position> beacons { };

    for (const auto &sensorInput: sensorsInput) {
        const auto sensor = parseSensor(sensorInput);
        sensors.push_back(sensor);

        auto contains = std::find_if(beacons.begin(), beacons.end(), [&] (const auto& be) {
            return be.x == sensor.nearestBeacon.x && be.y == sensor.nearestBeacon.y;
        });
        if (contains == beacons.end()) {
            beacons.push_back(sensor.nearestBeacon);
            std::cout << "Beacon added: " << sensor.nearestBeacon.x << ", " << sensor.nearestBeacon.y << "\n";
        }
    }

    auto index = 0;
    for (const auto& sensor: sensors) {
        const auto yDiff = std::abs(sensor.position.y - sensor.nearestBeacon.y);
        const auto xDiff = std::abs(sensor.nearestBeacon.x - sensor.position.x);
        const auto halfSize = std::abs(xDiff + yDiff);

        const auto t = sensor.position.y - rowToCheck;
        auto ta = t < halfSize;
        auto tb = t > -halfSize;
        if (ta  && tb) {
            const auto widthAtRow = std::abs(halfSize - std::abs(rowToCheck - sensor.position.y));

            auto range = Range { sensor.position.x - widthAtRow, sensor.position.x + widthAtRow };

            for (auto& existing: ranges) {
                existing.subtract(range);
            }

            if (range.isValid) {
                ranges.push_back(range);
            }
        }

        std::cout << "sensor " << index << " \n";
        for (const auto &item: ranges) {
            if (item.isValid) {
                std::cout << "range " << item.start << " to " << item.end << "\n";
            }
        }
        ++index;
    }

    // -2,-1,0,1,2 - 3,4,5,6,7 8,9 - 10,11,12,13,14,15,16,17 - 18,19,20,21,22 - 23,24

    auto sum = 0;
    for (const auto &range: ranges) {
        auto len = range.length();
        sum += len;
        auto test = 2;

        for (const auto &beacon: beacons) {
            if (range.isValid && beacon.x >= range.start && beacon.x <= range.end && beacon.y ==rowToCheck) {
                --sum;
            }
        }

        for (const auto &sensor: sensors) {
            if (range.isValid && sensor.position.x >= range.start && sensor.position.x <= range.end && sensor.position.y ==rowToCheck) {
                --sum;
            }
        }
    }

    return sum;
}

auto main() -> int {
    auto sensors = file::getLines("input.txt");

    const auto partTwo = 0;

    std::cout << "part 1: " << partOne(sensors) << "\npart 2: " << partTwo;
    return 0;
}