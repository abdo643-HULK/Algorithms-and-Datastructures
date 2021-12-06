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
    const int prime;

    int h1(const int key) const {
        return key % capacity;
    }

    int h2(const int key) const {
        return 1 + (key % (capacity - 2));
    }

    void swap(int *a, int *b) {
        if (*a == *b) return;
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
    }

    int calcIndex(const int h1, const int h2) const {
        return abs((h1 - h2) % capacity);
    }

    int getPrime()
    {
        // Iterating using for loop in reverse order
        for (int i = capacity - 1; i >= 1; i--) {

            // Initially assigning count to zero
            int cnt = 0;

            // Now, iterating from 2 upto the desired number
            // to be checked by dividing it with all no
            // in between [2 - no]
            for (int j = 2; j * j <= i; j++)

                // If number is divisible
                // means not a prime number
                if (i % j == 0)

                    // So simply move to next number
                    // to check for divisibility by
                    // incrementing the count variable
                    cnt++;

            // By now number is not divisible
            // hence count holds 0 till last
            if (cnt == 0)

                // It means it is a prime number so
                // return the number as it is a prime number
                return i;
        }

        // Returning a prime number
        return 3;
    }

public:
    // Allocates and initialize empty hashset
    explicit OrderedDoubleHashset(int initCapacity) : nrElements(0), capacity(initCapacity), prime(getPrime()) {
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

        int index = hash1;
        for (int i = 0; i < capacity; ++i) {
            if (key < current->element) swap(&key, &current->element);

            const int hash2 = h2(key);
            index = calcIndex(index, hash2);

            if (hashTable[index]->isDeleted) {
                hashTable[index]->element = key;
                hashTable[index]->isDeleted = false;
                return true;
            }
        }

        return false;
    }

    // removes the key (true if the key was removed,
    // false otherwise
    bool remove(int key) {
        if (!contains(key)) return false;
        --nrElements;
        const int hash1 = h1(key);
        const auto current = hashTable[hash1];

        // if the first element is deleted we can remove it
        if (!current->isDeleted && key == current->element) {
            return current->isDeleted = true;
        }

        int index = hash1;
        const int hash2 = h2(key);

        for (int i = 0; i < capacity; ++i) {
            index = calcIndex(index, hash2);

            if (!hashTable[index]->isDeleted && key == hashTable[index]->element) {
                hashTable[index]->isDeleted = true;
                return true;
            }
        }

        return false;
    }

    // Returns true if the key is in the hashset
    // false otherwise
    bool contains(int key) {
        const int hash1 = h1(key);
        auto current = hashTable[hash1];

        if (key <= current->element && current->isDeleted) {
            return false;
        } else if (key == current->element && !current->isDeleted) {
            return true;
        }


        int index = hash1;
        const int hash2 = h2(key);

        for (int i = 0; i < capacity; ++i) {
            index = calcIndex(index, hash2);

            if (!hashTable[index]->isDeleted && key == hashTable[index]->element) return true;
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
            os << (current->isDeleted ? "" : ("Element: " + to_string(current->element) + ", Index: " + to_string(i) + " -> "));
        }
        return os << "end";
    };
};

#endif //UE07_ORDEREDDOUBLEHASHSET_HPP
