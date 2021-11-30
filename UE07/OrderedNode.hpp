//
// Created by abous on 30/11/2021.
//

#ifndef UE07_ORDEREDNODE_HPP
#define UE07_ORDEREDNODE_HPP

#include <limits>


class OrderedNode {
private:
    static const int INIT_ELEMENT = std::numeric_limits<int>::max();

public:
    int element; // contains the data element
    bool isDeleted;

    // we need to start with the max because
    // in the Set we check if the key is smaller than
    // the element, and we initialize the set with "empty" nodes and not with nullptr.
    // Because we start with the biggest possible int we don't need to
    // check for special cases
    OrderedNode() : element(INIT_ELEMENT), isDeleted(true) {};

    OrderedNode(int key) : element(key), isDeleted(true) {};

    OrderedNode(int key, bool isDeleted) : element(key), isDeleted(isDeleted) {};
};

#endif //UE07_ORDEREDNODE_HPP
