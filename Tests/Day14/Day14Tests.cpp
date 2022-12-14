#include "file_utils.h"
#include "Day14.h"
#include <iostream>
#include "catch2/catch_test_macros.hpp"
#include "catch2/benchmark/catch_benchmark.hpp"

TEST_CASE("Day 14") {
    auto lines = file::getLines("input/Day14.txt");

    const auto partOne = Day14::partOne(lines);
    const auto partTwo = Day14::partTwo(lines);
    CHECK(partOne == 1406);
    CHECK(partTwo == 20870);

    std::cout << "part 1: " << partOne << "\npart 2: " << partTwo;

    BENCHMARK("Part One") {
        Day14::partOne(lines);
    };

    BENCHMARK("Part Two") {
        Day14::partTwo(lines);
    };
}

