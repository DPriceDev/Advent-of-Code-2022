cmake_minimum_required(VERSION 3.20.0)

add_library(day_09 Day09.cpp Day09.h)
target_link_libraries(day_09 PUBLIC utils)
target_compile_features(day_09 INTERFACE cxx_std_23)
target_include_directories(day_09 PUBLIC .)