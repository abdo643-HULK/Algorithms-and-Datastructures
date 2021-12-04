//
// Created by abous on 29/11/2021.
//

#include "ChainingHashset.hpp"
#include "OrderedDoubleHashset.hpp"

void printBoolean(bool value) {
    std::cout << "Found: " << (value ? "true" : "false") << "\n";
}

int main() {
    cout << "-------------- ChainingHashset ----------------" << "\n";
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
    OrderedDoubleHashset doubleHashset(7);
    doubleHashset.insert(15);
    doubleHashset.insert(2);
    doubleHashset.insert(43);
    doubleHashset.insert(4);
    doubleHashset.insert(18);

    doubleHashset.insert(21);

    cout << doubleHashset << "\n";

    doubleHashset.remove(18);

    cout << doubleHashset << "\n";

    cout << endl;
    return 0;
}