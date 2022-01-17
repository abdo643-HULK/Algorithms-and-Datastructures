//
// Created by abous on 06/12/2021.
//
#include "BoyerMoore.hpp"
#include "BruteForce.hpp"
#include <iostream>

constexpr int TEST_CASES = 1;

using namespace std;

void bruteForceTest(const string &text, const string &pattern);

void boyerMooreTest(string &&text, const string &pattern);

int main(int _argv, char **_args) {
    std::ifstream t("./big.txt");
    std::string text;
    t.seekg(0, std::ios::end);
    text.reserve(t.tellg());
    t.seekg(0, std::ios::beg);
    text.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

    const string patterns[] = {
            "a",
            "abacab",
            "ab",
            "def",
            "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzz",
            "bacaabaccebabacabbb"
    };

    int i = 1;
    for (const auto &pattern: patterns) {
        cout << "\n==================" << " Run " << i << " ==================" << "\n";
        bruteForceTest(text, pattern);
        boyerMooreTest(const_cast<string &&>(text), pattern);
        ++i;
    }

    return 0;
}

void boyerMooreTest(const string &text, const string &pattern) {
    cout << "-------------- BoyerMoore ----------------" << "\n";
    const auto then = std::chrono::steady_clock::now();

    int matches = 0;
    for (int i = 0; i < TEST_CASES; ++i) {
        int index = -1;
        int count = -1;

        BoyerMoore bm(pattern, text);

        do {
            index = bm.Match(++index);
            count++;
            (index > -1) && ++matches;
        } while (index != -1);
    }

    const auto now = std::chrono::steady_clock::now();
    cout << "Time taken: " <<
         std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count() << "ms" << endl;

    cout << matches << endl;
}

void boyerMooreTest(string &&text, const string &pattern) {
    cout << "-------------- BoyerMoore ----------------" << "\n";
    const auto then = std::chrono::steady_clock::now();

    int matches = 0;
    for (int i = 0; i < TEST_CASES; ++i) {
        int index = -1;
        int count = -1;

        BoyerMoore bm(pattern, forward<string &&>(text));

        do {
            index = bm.Match(++index);
            count++;
            (index > -1) && ++matches;
        } while (index != -1);
    }

    const auto now = std::chrono::steady_clock::now();
    cout << "Time taken: " <<
         std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count() << "ms" << endl;

    cout << matches << endl;
}

void bruteForceTest(const string &text, const string &pattern) {
    cout << "-------------- BruteForce ----------------" << "\n";
    const auto then = std::chrono::steady_clock::now();

    int matches = 0;
    for (int i = 0; i < TEST_CASES; ++i) {
        int index = -1;
        int count = -1;

        BruteForce bf(pattern, text);

        do {
            index = bf.Match(++index);
            count++;
            (index > -1) && ++matches;
        } while (index != -1);
    }

    const auto now = std::chrono::steady_clock::now();
    cout << "Time taken: " <<
         std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count() << "ms" << endl;

    cout << matches << endl;
}