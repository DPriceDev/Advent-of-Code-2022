#include "file_utils.h"
#include "Day06.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>

TEST_CASE("Day 06") {
    auto lines = file::readText("input/Day06.txt");

    REQUIRE(Day06::partOne(lines) == 1582);
    REQUIRE(Day06::partTwo(lines) == 3588);

    REQUIRE(Day06::partOneAlt(lines) == 1582);
    REQUIRE(Day06::partTwoAlt(lines) == 3588);

    BENCHMARK("Part One") {
        Day06::partOne(lines);
    };

    BENCHMARK("Part One Alternative") {
        Day06::partOneAlt(lines);
    };

    BENCHMARK("Part Two") {
        Day06::partTwo(lines);
    };

    BENCHMARK("Part Two Alternative") {
        Day06::partTwoAlt(lines);
    };
}

