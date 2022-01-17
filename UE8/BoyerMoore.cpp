//
// Created by abous on 06/12/2021.
//

#include "BoyerMoore.hpp"

#include <utility>

using namespace std;

BoyerMoore::BoyerMoore(const string &pattern, string &&text) :
        pattern(pattern),
        text(forward<string &>(text)),
        match(new int[pattern.length()]) {
    calculateLast();
    calculateMatchTable();
}

BoyerMoore::BoyerMoore(const string &pattern, const string &text) :
        pattern(pattern),
        text(text),
        match(new int[pattern.length()]) {
    calculateLast();
    calculateMatchTable();
}

void BoyerMoore::calculateLast() {
    fill(begin(last), end(last), -1);

    int i = 0;
    for (const auto &elem: pattern) {
        const auto asciiCode = static_cast<uint8_t>(elem);
        last[asciiCode] = i;
        ++i;
    }
}

void BoyerMoore::calculateMatchTable() {
    const auto m = static_cast<int>(pattern.length());

    int j = 0;
    while (j < m) {
        bool found = false;
        int s = 0;

        const auto partToMatch = pattern.substr(j + 1, m - 1);

        while (s <= j && !found) {
            ++s;
            if (j <= 0) break;

            const auto start = j + 1 - s;
            const auto length = m - s;
            const auto suffixPart = pattern.substr(start, length);

            if (((partToMatch.find(suffixPart) != string::npos) || j == m - 1) &&
                (pattern[j] != pattern[j - s])) {
                found = true;
            }
        }

        while ((j < s && s < m) && !found) {
            const auto length = m - s;
            const auto suffixPart = pattern.substr(0, length);

            if (partToMatch.find(suffixPart) != string::npos) {
                found = true;
                break;
            }

            ++s;
        }

        if (!found) s = m;
        match[j++] = s;
    }
}

int BoyerMoore::Match(int startIndex) {
    const auto m = pattern.length();
    const auto n = text.length();

    auto i = startIndex + m - 1;
    auto j = m - 1;
    do {
        if (pattern[j] == text[i]) {
            if (j == 0) return static_cast<int>(i);
            --i;
            --j;
            continue;
        }

        i += m - j - 1;
        const auto asciiCode = static_cast<uint8_t>(text[i]);
        i += max(static_cast<int>(j - last[asciiCode]), match[j]);
        j = m - 1;
    } while (i < n - 1);

    return -1;
}

BoyerMoore::~BoyerMoore() {
    delete[] match;
}