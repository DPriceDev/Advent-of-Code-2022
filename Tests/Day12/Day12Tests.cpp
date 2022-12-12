#include "file_utils.h"
#include "Day12.h"
#include <iostream>
#include "catch2/catch_test_macros.hpp"
#include "catch2/benchmark/catch_benchmark.hpp"

TEST_CASE("Day 12") {
    const auto lines = file::getLines("input/Day12.txt");

    const auto partOne = Day12::partOne(lines);
    const auto partTwo = Day12::partTwo(lines);
    CHECK(partOne == 497);
    CHECK(partTwo == 492);

    std::cout << "part 1: " << partOne << "\npart 2: " << partTwo;

    BENCHMARK("Part One") {
        Day12::partOne(lines);
    };

    BENCHMARK("Part Two") {
        Day12::partTwo(lines);
    };
}

