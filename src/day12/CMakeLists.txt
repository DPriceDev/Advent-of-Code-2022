cmake_minimum_required(VERSION 3.20.0)

add_library(day_12 Day12.cpp Day12.h)
target_link_libraries(day_12 PUBLIC utils)
target_compile_features(day_12 INTERFACE cxx_std_23)
target_include_directories(day_12 PUBLIC .)
