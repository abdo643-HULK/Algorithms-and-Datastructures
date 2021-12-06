cmake_minimum_required(VERSION 3.21)
project(UE8)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(
        UE8
        main.cpp
        BruteForce.cpp BruteForce.hpp
        BoyerMoore.cpp BoyerMoore.hpp
)
