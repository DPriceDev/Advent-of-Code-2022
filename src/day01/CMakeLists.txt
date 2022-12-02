cmake_minimum_required(VERSION 3.20.0)

add_executable(day_01 Day01.cpp)
target_link_libraries(day_01 PUBLIC utils)
target_compile_features(day_01 INTERFACE cxx_std_23)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
