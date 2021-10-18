cmake_minimum_required(VERSION 3.20)
project(UE2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(UE2
        main.cpp
        LinkedList.cpp
        LinkedList.hpp
        ListNode.cpp ListNode.hpp)
