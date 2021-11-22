#include <iostream>
#include <string>
#include "BTS.hpp"

using namespace std;

void printBoolean(bool value) {
	std::cout << (value ? "true" : "false") << "\n";
}

int main() {
	const auto end = "\n";
	auto tree = BST<int, int>();

	tree.insertElement(2, 2);
	tree.insertElement(1, 3);
	tree.insertElement(23, 6);
	tree.insertElement(8, 9);

	tree.printInOrder();

	printBoolean(tree.containsKey(3));

	cout << "Max: " << (*tree.getMaximum()) << end;

	cout << "Min: " << (*tree.getMinimum()) << end;

	const auto foundValue = tree.getValue(8);

	cout << "Found: " << (foundValue != nullptr ? to_string((*foundValue)) : "none") << end;

	tree.deleteElement(23);

	tree.printInOrder();

	return 0;
}
