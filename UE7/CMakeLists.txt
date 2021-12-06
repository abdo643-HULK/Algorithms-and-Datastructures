cmake_minimum_required(VERSION 3.20)
project(UE7)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        UE7
        main.cpp
        ChainingNode.hpp
        ChainingHashset.hpp
        OrderedNode.hpp
        OrderedDoubleHashset.hpp
)
