cmake_minimum_required(VERSION 3.20.0)

add_library(utils INTERFACE file_utils.h string_utils.h)
target_include_directories(utils INTERFACE .)
target_compile_features(utils INTERFACE cxx_std_23)
