#include <iostream>
#include <string>
#include "LinkedList.hpp"


int main()
{
    using namespace std;
    const auto list = new LinkedList();

    list->addFirst(5);
    list->addFirst(4);
    list->addFirst(10);
    list->addFirst(7);
    list->addFirst(8);

    cout << "Value from RemoveAt: " << list->removeAt(2) << "\n";

    cout << "Size: " << list->size() << "\n";

    list->printElements();

    const int index = 2;
    cout << "GetAt(" << index << "): " << list->getAt(index) << "\n";

    const int searchedValue = 5;
    const string contains = list->contains(searchedValue) ? "yes" : "no";

    cout << "Contains " << searchedValue << ": " << contains << "\n";

    list->sortASC();

    cout << "Head: " << list->getFirst() << "\n";
    cout << "Tail: " << list->getLast() << "\n";

    list->sortDES();

    cout << "Head: " << list->getFirst() << "\n";
    cout << "Tail: " << list->getLast() << "\n";

    list->clear();

    list->addLast(55);
    list->addSorted(35);

    cout << "Size: " << list->size() << "\n";

    list->printElements();

    #ifdef _WIN32
        cout << "\n" << "After Clear: " << "\n";
    #else
        cout << "\n" << "\e[1m" << "After Clear: " << "\e[0m" << "\n";
    #endif
    //list->clear();

    cout << "Head: " << list->getFirst() << "\n";
    cout << "Tail: " << list->getLast() << "\n";
    cout << "Size: " << list->size() << "\n";

    cout << "Value from removeFirst: " << list->removeFirst() << "\n";
    cout << "Value from removeLast: " << list->removeLast() << "\n";

    delete list;
    return 0;
}
