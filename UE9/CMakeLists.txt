cmake_minimum_required(VERSION 3.21)
project(UE9)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(
        UE9
        main.cpp main.hpp
        Graph.cpp Graph.hpp
        MyVertex.hpp)
