cmake_minimum_required(VERSION 3.0)
project(advent_of_code_2022_cpp)

set(CMAKE_CXX_STANDARD 23)

Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.2.0
)

FetchContent_MakeAvailable(Catch2)

add_subdirectory(src/utils)

add_subdirectory(src)

add_subdirectory(tests)