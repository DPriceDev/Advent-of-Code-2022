#include "file_utils.h"
#include "Day11.h"
#include "catch2/catch_test_macros.hpp"
#include "catch2/benchmark/catch_benchmark.hpp"

TEST_CASE("Day 11") {
    auto lines = file::getLines("input/Day11.txt");

    REQUIRE(Day11::partOne(lines) == 51075);
    REQUIRE(Day11::partTwo(lines) == 11741456163);

    BENCHMARK("Part One") {
        Day11::partOne(lines);
    };

    BENCHMARK("Part Two") {
        Day11::partTwo(lines);
    };
}

