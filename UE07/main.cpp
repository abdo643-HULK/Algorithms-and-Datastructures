//
// Created by abous on 29/11/2021.
//

#include "ChainingHashset.hpp"
#include "OrderedDoubleHashset.hpp"

void printBoolean(bool value) {
    std::cout << "Found: " << (value ? "true" : "false") << "\n";
}

int main() {
    ChainingHashset set(5);

    set.insert(1);
    set.insert(1);
    set.insert(15);
    set.insert(17);
    set.insert(110);
    set.insert(159);
    set.insert(1);
    set.insert(159);
    set.insert(137);
    set.insert(207);

    set.remove(1);

    cout << "List: \n" << set;

    cout << "size: " << set.size() << "\n";

    cout << "-------------- OrderedHashSet ----------------" << "\n";
    OrderedDoubleHashset doubleHashset(5);

    cout << (doubleHashset.insert(5) ? "true" : "false") << "\n";

    printBoolean(doubleHashset.contains(5));

    cout << endl;
    return 0;
}