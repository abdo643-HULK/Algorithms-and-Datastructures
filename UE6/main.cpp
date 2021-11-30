//
// Created by abous on 22/11/2021.
//
#include <string>
#include "AVLTree.hpp"

void printBoolean(bool value) {
    std::cout << "Found: " << (value ? "true" : "false") << "\n";
}

void print(string v) {
    cout << v << "\n";
}

int main() {
    AVLTree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);
    tree.insert(8);

    print("Size: " + to_string(tree.size()));
    print("Height: " + to_string(tree.height()));
    printBoolean(tree.find(10));

    tree.printInOrder();

    tree.deleteElement(4);

    tree.printInOrder();
    print("Size: " + to_string(tree.size()));

    return 0;
}