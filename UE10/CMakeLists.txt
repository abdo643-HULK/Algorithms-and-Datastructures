cmake_minimum_required(VERSION 3.21)
project(UE10)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(
        UE10
        main.cpp main.hpp
        Graph.cpp Graph.hpp
        MyVertex.hpp PQElement.hpp Geeks.cpp Geeks.hpp)
