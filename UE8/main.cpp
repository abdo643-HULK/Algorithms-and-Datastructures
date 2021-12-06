//
// Created by abous on 06/12/2021.
//
#include "BoyerMoore.hpp"
#include "BruteForce.hpp"
#include <iostream>

using namespace std;

int main() {
    cout << "-------------- BruteForce ----------------" << "\n";
    std::ifstream t("./big.txt");
    std::string text;
    t.seekg(0, std::ios::end);
    text.reserve(t.tellg());
    t.seekg(0, std::ios::beg);
    text.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

    const auto pattern = "a";

    const auto then = std::chrono::steady_clock::now();
    int matches = 0;
    for (int i = 0; i < 1; ++i) {
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

    return 0;
}