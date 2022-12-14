cmake_minimum_required(VERSION 3.20.0)

add_executable(day_14 Day14.cpp)
target_link_libraries(day_14 PUBLIC utils)
target_compile_features(day_14 INTERFACE cxx_std_23)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
