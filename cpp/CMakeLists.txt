cmake_minimum_required(VERSION 3.10)
project(dijkstra_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(dijkstra_cpp dijkstra.cpp)

# Enable optimizations in release mode
set(CMAKE_BUILD_TYPE Release)
