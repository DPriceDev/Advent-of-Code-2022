#include "file_utils.h"
#include "Day13.h"
#include <iostream>
#include "catch2/catch_test_macros.hpp"
#include "catch2/benchmark/catch_benchmark.hpp"

TEST_CASE("Day 13") {
    auto lines = file::getLines("input/Day13.txt");

    const auto partOne = Day13::partOne(lines);
    const auto partTwo = Day13::partTwo(lines);
    CHECK(partOne == 4894);
    CHECK(partTwo == 24180);

    std::cout << "part 1: " << partOne << "\npart 2: " << partTwo;

    BENCHMARK("Part One") {
        Day13::partOne(lines);
    };

    BENCHMARK("Part Two") {
        Day13::partTwo(lines);
    };
}

