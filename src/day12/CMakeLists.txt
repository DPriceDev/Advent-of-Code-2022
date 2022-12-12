cmake_minimum_required(VERSION 3.20.0)

add_executable(day_12 Day12.cpp)
target_link_libraries(day_12 PUBLIC utils)
target_compile_features(day_12 INTERFACE cxx_std_23)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
