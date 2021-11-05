cmake_minimum_required(VERSION 3.20)
project(UE3)

set(CMAKE_CXX_STANDARD 14)

add_executable(UE3 main.cpp MinHeap.cpp MinHeap.hpp quicksort_mot.h quicksort_mot.cpp)
