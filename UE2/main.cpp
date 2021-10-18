#include <iostream>
#include "LinkedList.hpp"


int main(int argc, char const *argv[])
{
    const auto list = new LinkedList();

    list->addFirst(5);
    list->addFirst(4);
    list->addFirst(10);
    list->addFirst(7);
    list->addFirst(8);

    std::cout << list->contains(1) << "\n";

    list->printElements();

    return 0;
}
