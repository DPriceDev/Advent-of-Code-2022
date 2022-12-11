cmake_minimum_required(VERSION 3.20.0)

add_library(day_10 Day10.cpp Day10.h)
target_link_libraries(day_10 PUBLIC utils)
target_compile_features(day_10 INTERFACE cxx_std_23)
target_include_directories(day_10 PUBLIC .)
#target_compile_options(day_10 PRIVATE -Wall -Wextra -Wpedantic -Werror)
