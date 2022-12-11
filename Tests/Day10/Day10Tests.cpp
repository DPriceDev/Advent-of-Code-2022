#include "file_utils.h"
#include "Day10.h"
#include "catch2/catch_test_macros.hpp"
#include "catch2/benchmark/catch_benchmark.hpp"

TEST_CASE("Day 10") {
    const auto lines = file::getLines("input/Day10.txt");

    CHECK(Day10::partOne(lines) == 12880);
    Day10::partTwo(lines);

    BENCHMARK("Part One") {
        Day10::partOne(lines);
    };

    BENCHMARK("Part Two") {
        Day10::partTwo(lines);
    };
}
