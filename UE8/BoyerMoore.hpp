//
// Created by abous on 06/12/2021.
//

#ifndef UE8_BOYERMOORE_HPP
#define UE8_BOYERMOORE_HPP

#include <fstream>
#include <streambuf>
#include <chrono>
#include <algorithm>

class BoyerMoore {
    std::string pattern;
    std::string text;

    int last[256]; // exactly as long as the alphabet
    int *match; // exactly as long as the pattern
    void calculateLast();
    void calculateMatchTable();
public:
    BoyerMoore(std::string pattern, std::string text);
    ~BoyerMoore();
    int Match(int startIndex);
};


#endif //UE8_BOYERMOORE_HPP
