#include "file_utils.h"
#include "Day06.h"
#include <iostream>
#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>

TEST_CASE("Day 06") {
    auto lines = file::readText("input/Day06.txt");

    const auto partOne = Day06::partOne(lines);
    const auto partTwo = Day06::partTwo(lines);
    CHECK(partOne == 1582);
    CHECK(partTwo == 3588);

    const auto partOneAlt = Day06::partOneAlt(lines);
    const auto partTwoAlt = Day06::partTwoAlt(lines);
    CHECK(partOneAlt == 1582);
    CHECK(partTwoAlt == 3588);

    std::cout << "part 1: " << partOne << "\npart 2: " << partTwo;
    std::cout << "\npart 1 alt: " << partOne << "\npart 2 alt: " << partTwo;

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

