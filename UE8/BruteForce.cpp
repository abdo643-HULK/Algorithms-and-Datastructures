//
// Created by abous on 06/12/2021.
//

#include "BruteForce.hpp"

using namespace std;

BruteForce::BruteForce(std::string pattern, std::string text) :
        pattern(move(pattern)),
        text(move(text)) {}

int BruteForce::Match(int startIndex) {
    const auto m = pattern.length();
    const auto n = text.length();

    for (int i = startIndex; i < n - m; ++i) {
        int j = 0;

        while (j < m && text[i + j] == pattern[j]) ++j;

        if (j == m) return i;
    }

    return -1;
}

BruteForce::~BruteForce() = default;