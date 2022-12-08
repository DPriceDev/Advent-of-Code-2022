cmake_minimum_required(VERSION 3.20.0)

add_executable(day_08 Day08.cpp)
target_link_libraries(day_08 PUBLIC utils)
target_compile_features(day_08 INTERFACE cxx_std_23)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
