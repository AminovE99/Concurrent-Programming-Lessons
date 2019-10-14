cmake_minimum_required(VERSION 3.15)
project(Concurrent-Programming-Lessons)

set(CMAKE_CXX_STANDARD 14)

add_library(ParrarelTasks task1.cpp task1.h)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fopenmp")

set(SOURCE_FILES task1.cpp)
add_executable(Concurrent-Programming-Lessons ${SOURCE_FILES})
