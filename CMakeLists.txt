cmake_minimum_required(VERSION 3.6)
project(nvtest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

set(SOURCE_FILES main.cpp)
add_executable(nvtest ${SOURCE_FILES})

add_executable(nvtest_openmp openmp_main.cpp)