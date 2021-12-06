//
// Created by abous on 06/12/2021.
//

#ifndef UE8_BRUTEFORCE_HPP
#define UE8_BRUTEFORCE_HPP

#include <fstream>
#include <streambuf>
#include <chrono>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>

class BruteForce {
    const std::string pattern;
    std::string text;

public:
    BruteForce(std::string  pattern, std::string  text);

    ~BruteForce();

    int Match(int startIndex);
};


#endif //UE8_BRUTEFORCE_HPP
