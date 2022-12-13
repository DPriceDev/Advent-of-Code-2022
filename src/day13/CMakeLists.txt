cmake_minimum_required(VERSION 3.20.0)

add_library(day_13 Day13.cpp)
target_link_libraries(day_13 PUBLIC utils)
target_compile_features(day_13 INTERFACE cxx_std_23)
target_include_directories(day_13 PUBLIC .)
