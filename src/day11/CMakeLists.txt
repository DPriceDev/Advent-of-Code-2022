cmake_minimum_required(VERSION 3.20.0)

FIND_PACKAGE(Boost REQUIRED)

add_executable(day_11 Day11.cpp)
target_link_libraries(day_11 PUBLIC utils  Boost::boost)
target_compile_features(day_11 INTERFACE cxx_std_23)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
