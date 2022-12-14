cmake_minimum_required(VERSION 3.20.0)

add_library(day_14 Day14.cpp Day14.h)
target_link_libraries(day_14 PUBLIC utils)
target_compile_features(day_14 INTERFACE cxx_std_23)
target_include_directories(day_14 PUBLIC .)
