cmake_minimum_required(VERSION 3.20.0)

add_executable(day_10 Day10.cpp)
target_link_libraries(day_10 PUBLIC utils)
target_compile_features(day_10 INTERFACE cxx_std_23)
#target_compile_options(day_09 PRIVATE -Wall -Wextra -Wpedantic -Werror)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
