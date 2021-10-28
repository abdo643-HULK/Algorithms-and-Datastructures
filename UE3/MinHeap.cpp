//
// Created by Abdo on 28.10.21.
//

#include "MinHeap.hpp"

//--------------------------------------//
//--------------private-----------------//
//--------------------------------------//


int MinHeap::parent(int index) {
    const int idx = (int) (index - 1) / 2;
    if (idx < 0 || idx > nrElements - 1) return -1;
    return heap[idx];
}

int MinHeap::leftChild(int index) {
    const int idx = 2 * index + 1;
    if (idx < 0 || idx > nrElements - 1) return -1;
    return heap[idx];
}

int MinHeap::rightChild(int index) {
    const int idx = 2 * index + 2 ;
    if (idx < 0 || idx > nrElements - 1) return -1;
    return heap[idx];
}

void MinHeap::swap(int index1, int index2) {
    // just skip swapping if both are the same
    // if we would be working with big objects
    // checking if both are the same should be faster
    // but in our case I think it doesn't really matter
    if (heap[index1] != heap[index2]) {
        // xor should be faster and more memory efficient
        heap[index1] ^= heap[index2];
        heap[index2] ^= heap[index1];
        heap[index1] ^= heap[index2];
        /// std tmp var
        // const int tmp = heap[index2];
        // heap[index1] = heap[index2];
        // heap[index2] = tmp;
    }


}

//--------------------------------------//
//---------------public-----------------//
//--------------------------------------//

MinHeap::MinHeap(int initCapacity) {
    heapCapacity = initCapacity;
    heap = new int[initCapacity];
    nrElements = 0;
}

bool MinHeap::isEmpty() const {
    return nrElements == 0;
}

int MinHeap::size() const {
    return nrElements;
}

int MinHeap::min() const {
    if (isEmpty()) return numeric_limits<int>::min();
    return heap[0];
}

void MinHeap::insert(int data) {
    if (nrElements == heapCapacity - 1) {
        const auto newHeap = new int[heapCapacity * 2];
        heapCapacity = heapCapacity * 2;

        // vom Michi das Ok bekommen copy zu nutzen
        // memcpy(newHeap, heap, sizeof(int) * nrElements);
        // copy(heap, heap + nrElements, newHeap);

        // &heap[0] == heap, &heap[nrElements] == heap + nrElements;
        copy(&heap[0], &heap[nrElements], newHeap);
        delete[] heap;
        heap = newHeap;
    }
}

string MinHeap::toString() {
    string heapString = "";

    for (int i = 0; i < nrElements / 2; ++i) {
        heapString.append("Parent: " +  to_string(heap[i]));
        heapString.append(" Left Child: " + to_string(heap[2 * i + 1]));
        heapString.append(" Right Child: " + to_string(heap[2 * i + 2]) + "\n");
    }

    return heapString;
}

MinHeap::~MinHeap() {
    printf("MinHeap Destructor called");
    delete[] heap;
}