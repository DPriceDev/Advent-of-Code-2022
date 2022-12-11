cmake_minimum_required(VERSION 3.20.0)

add_library(day_06 Day06.cpp Day06_alternative.cpp Day06.h)
target_link_libraries(day_06 PUBLIC utils)
target_include_directories(day_06 PUBLIC .)
target_compile_features(day_06 INTERFACE cxx_std_23)