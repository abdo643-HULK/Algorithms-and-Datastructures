//
// Created by abous on 29/11/2021.
//

#ifndef UE07_CHAININGHASHSET_HPP
#define UE07_CHAININGHASHSET_HPP

#include <iostream>
#include "ChainingNode.hpp"

using namespace std;

class ChainingHashset {
private:
    // Pointer to array representing the hashset
    ChainingNode **hashTable;

    int nrElements;
    const int capacity;

    int hashCode(int key) {
        return key % capacity;
    }

public:
    // Allocates and initialize empty hashset
    explicit ChainingHashset(int initCapacity) : nrElements(0), capacity(initCapacity) {
        hashTable = new ChainingNode *[initCapacity];
        for (int i = 0; i < initCapacity; ++i) {
            hashTable[i] = nullptr;
        }
    }

    // Returns the number of stored keys
    int size() { return nrElements; }

    // Inserts the key into the hashset
    // returns true if key has been inserted
    // false otherwise
    bool insert(int key) {
        if (contains(key)) return false;

        const int hash = hashCode(key);
        const auto next = hashTable[hash];
        const auto newNode = new ChainingNode(key, next);
        hashTable[hash] = newNode;
        ++nrElements;
        return true;
    }

    // Returns true if the key is in the hashset
    // false otherwise
    bool contains(int key) {
        const int hash = hashCode(key);
        // because the hash can get bigger than the max, we
        // need to check it
//        if (hash >= capacity) return false;

        auto current = hashTable[hash];
        while (current != nullptr) {
            if (current->element == key) return true;
            current = current->next;
        }

        return false;
    }

    // removes the key (true if the key was removed, false otherwise
    bool remove(int key) {
        if (!contains(key)) return false;

        const int hash = hashCode(key);
        auto current = hashTable[hash];
        while (current != nullptr) {
            if (current->next && current->next->element == key) {
                --nrElements;
                const auto next = current->next->next;
                delete current->next;
                return current->next = next;
            };
            current = current->next;
        }

        return false;
    };

    //removes all elements from the set
    void clear() {
        nrElements = 0;
        for (int i = 0; i < capacity; ++i) {
            auto current = hashTable[i];
            while (current != nullptr) {
                const auto next = current->next;
                delete current;
                current = next;
            }
        }

        delete[] hashTable;
    }

    // Deallocate memory for the chained nodes and the array
    ~ChainingHashset() { clear(); }

    friend std::ostream &operator<<(std::ostream &os, ChainingHashset &chs) {
        for (int i = 0; i < chs.capacity; ++i) {
            auto current = chs.hashTable[i];
            if (!current) cout << "empty";
            while (current != nullptr) {
                os << current->element << " -> ";
                current = current->next;
            }
            os << "\n";
        }
        return os << endl;
    }
};

#endif //UE07_CHAININGHASHSET_HPP
