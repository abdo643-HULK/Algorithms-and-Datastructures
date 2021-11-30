cmake_minimum_required(VERSION 3.20)
project(UE07)

set(CMAKE_CXX_STANDARD 14)

add_executable(UE07
        main.cpp ChainingNode.hpp ChainingHashset.hpp OrderedDoubleHashset.hpp)
