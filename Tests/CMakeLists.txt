cmake_minimum_required(VERSION 3.20.0)

add_executable(tests
        day06/Day06Tests.cpp
        Day10/Day10Tests.cpp
        day11/Day11Tests.cpp
)
target_link_libraries(tests PRIVATE
        day_06
        day_10
        day_11
        util
)
target_compile_features(tests INTERFACE cxx_std_23)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

add_custom_command(
        TARGET tests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/input
        ${CMAKE_CURRENT_BINARY_DIR}/input
)

include(CTest)
include(Catch)
catch_discover_tests(
        tests
        TEST_PREFIX "tests."
        OUTPUT_DIR .
        OUTPUT_PREFIX "tests."
)