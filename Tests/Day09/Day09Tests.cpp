#include "file_utils.h"
#include "Day09.h"
#include <iostream>
#include "catch2/catch_test_macros.hpp"
#include "catch2/benchmark/catch_benchmark.hpp"

TEST_CASE("Day 09") {
    const auto lines = file::getLines("input/Day09.txt");

    const auto partOne = Day09::partOne(lines);
    const auto partTwo = Day09::partTwo(lines);
    CHECK(partOne == 6406);
    CHECK(partTwo == 2643);

    std::cout << "part 1: " << partOne << "\npart 2: " << partTwo;

    BENCHMARK("Part One") {
        Day09::partOne(lines);
    };

    BENCHMARK("Part Two") {
        Day09::partTwo(lines);
    };
}
