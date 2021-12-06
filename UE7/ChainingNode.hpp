//
// Created by abous on 29/11/2021.
//

#ifndef UE07_CHAININGNODE_HPP
#define UE07_CHAININGNODE_HPP

class ChainingNode {
public:
    int element; // contains the data element
    ChainingNode *next; // pointer to the next element in the

    ChainingNode() : element(0), next(nullptr) {};

    ChainingNode(int d) : element(d), next(nullptr) {};

    ChainingNode(int d, ChainingNode *n) : element(d), next(n) {};
};

#endif //UE07_CHAININGNODE_HPP
