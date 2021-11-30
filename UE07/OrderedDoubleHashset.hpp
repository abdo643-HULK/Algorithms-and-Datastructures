//
// Created by abous on 29/11/2021.
//

#ifndef UE07_ORDEREDDOUBLEHASHSET_HPP
#define UE07_ORDEREDDOUBLEHASHSET_HPP

#include <iostream>
#include "OrderedNode.hpp"

using namespace std;

class OrderedDoubleHashset {
private:
    // Pointer to array representing the hashset
    OrderedNode **hashTable;

    int nrElements;
    const int capacity;

    int h1(const int key) const {
        return key % capacity;
    }

    int h2(const int key) const {
        return 1 + (key % capacity - 2);
    }

    void swap(int *a, int *b) {
        if (*a == *b) return;
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
    }

    int calcIndex(const int h1, const int h2) const {
        return (h1 - h2) % capacity;
    }

public:
    // Allocates and initialize empty hashset
    explicit OrderedDoubleHashset(int initCapacity) : nrElements(0), capacity(initCapacity) {
        hashTable = new OrderedNode *[initCapacity];
        // for more info why I am not initializing with
        // nullptr, look in OrderedNode
        for (int i = 0; i < initCapacity; ++i) {
            hashTable[i] = new OrderedNode();
        }
    }

    // Returns the number of stored keys
    int size() { return nrElements; }

    // Inserts the key into the hashset
    // returns true if key has been inserted
    // false otherwise
    bool insert(int key) {
        if (contains(key) || nrElements == capacity) return false;
        ++nrElements;
//        const auto newNode = new OrderedNode(key);
        const int hash1 = h1(key);
        auto current = hashTable[hash1];

        // if the first element is deleted we can remove it
        if (current->isDeleted && key <= current->element) {
            current->isDeleted = false;
            current->element = key;
            return true;
        }

        if (key < current->element) {
            swap(&key, &current->element);
        }

        const auto hash2 = h2(key);

        for (int i = 0; i < capacity; ++i) {
            if (current->element > key) {
                key ^= current->element;
                current->element ^= key;
                key ^= current->element;
            }

            const int index = (hash1 - hash2) % capacity;

            if (hashTable[index]->isDeleted) {
                return true;
            }
        }

        return false;
    }

    // removes the key (true if the key was removed,
    // false otherwise
    bool remove(int key) {
        if (!contains(key)) return false;
    }

    // Returns true if the key is in the hashset
    // false otherwise
    bool contains(int key) {
        const int hash1 = h1(key);
        auto current = hashTable[hash1];

        if (key <= current->element && current->isDeleted) {
            return false;
        } else if(key == current->element && !current->isDeleted) {
            return true;
        }

        const int hash2 = h2(key);

        int index = calcIndex(hash1, hash2);
        while (current->element <= key) {
            current = hashTable[index];
            if (current->element == key && !current->isDeleted) return true;
            index = calcIndex(index, hash2);
        }

        return false;
    }


    // removes all elements from the set
    void clear() {
        if (nrElements == 0) return;
        nrElements = 0;
        for (int i = 0; i < capacity; ++i) {
            delete hashTable[i];
        }
        delete[] hashTable;
    }

    // Deallocate memory for the chained nodes and the array
    ~OrderedDoubleHashset() { clear(); }

    friend std::ostream &operator<<(std::ostream &os, OrderedDoubleHashset &chs) {
        for (int i = 0; i < chs.capacity; ++i) {
            const auto current = chs.hashTable[i];
            os << current->isDeleted ? "" : (to_string(current->element) + " -> ");
        }
        return os;
    };
};

#endif //UE07_ORDEREDDOUBLEHASHSET_HPP
