#include "file_utils.h"
#include "Day11.h"
#include <iostream>
#include "catch2/catch_test_macros.hpp"
#include "catch2/benchmark/catch_benchmark.hpp"

TEST_CASE("Day 11") {
    auto lines = file::getLines("input/Day11.txt");

    const auto partOne = Day11::partOne(lines);
    const auto partTwo = Day11::partTwo(lines);
    CHECK(partOne == 51075);
    CHECK(partTwo == 11741456163);

    std::cout << "part 1: " << partOne << "\npart 2: " << partTwo;

    BENCHMARK("Part One") {
        Day11::partOne(lines);
    };

    BENCHMARK("Part Two") {
        Day11::partTwo(lines);
    };
}

