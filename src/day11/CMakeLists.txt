cmake_minimum_required(VERSION 3.20.0)

add_library(day_11 Day11.cpp)
target_link_libraries(day_11 PUBLIC utils)
target_compile_features(day_11 INTERFACE cxx_std_23)
target_include_directories(day_11 PUBLIC .)