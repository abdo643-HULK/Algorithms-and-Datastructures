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
    return idx;
}

int MinHeap::leftChild(int index) {
    const int idx = 2 * index + 1;
    if (idx < 0 || idx > nrElements - 1) return -1;
    return idx;
}


int MinHeap::rightChild(int index) {
    const int idx = 2 * index + 2;
    if (idx < 0 || idx > nrElements - 1) return -1;
    return idx;
}

void MinHeap::upHeap(int index) {
    while ((nrElements >= 0) && (heap[index] < heap[parent(index)])) {
        swap(index, parent(index));
        index = parent(index);
    }
}

// Michael's max_heapify modified, so it works
// with a standard Heap (Min-Heap)
//void MinHeap::downHeap(int index) {
//    const int left = leftChild(index);
//    const int right = rightChild(index);
//
//    const int v = heap[index];
//    int smallest = index;
//
//    if (left != -1 && heap[left] < v) {
//        smallest = left;
//    }
//
//    if (right != -1 && heap[right] < heap[smallest]) {
//        smallest = right;
//    }
//
//    if (smallest != index) {
//        swap(index, smallest);
//        downHeap(smallest);
//    }
//}

void MinHeap::downHeap(int index) {
    const int left = leftChild(index);
    const int right = rightChild(index);

    if (left == -1 || right == -1) return;

    const int leftValue = heap[left];
    const int rightValue = heap[right];
    const int smallest = (leftValue < rightValue) ? left : right;

    swap(index, smallest);
    downHeap(smallest);
}

// just skip swapping if both are the same
// if we would be working with big objects
// checking if both are the same should be faster
// but in our case I think it doesn't really matter
void MinHeap::swap(int index1, int index2) {
    if (heap[index1] != heap[index2]) {
        /// std tmp var
        // const int tmp = heap[index2];
        // heap[index1] = heap[index2];
        // heap[index2] = tmp;

        // xor should be faster and more memory efficient
        heap[index1] ^= heap[index2];
        heap[index2] ^= heap[index1];
        heap[index1] ^= heap[index2];
    }
}

// could be a boolean but I like int/int8 from C
int8 MinHeap::resizeHeap() {
    try {
        cout << "resizing Heap" << "\n";
        const auto newHeap = new int[heapCapacity * 2];
        heapCapacity = heapCapacity * 2;

        // vom Michi das Ok bekommen copy zu nutzen

        // memcpy(newHeap, heap, sizeof(int) * nrElements);
        // copy(heap, heap + nrElements, newHeap);
        copy(&heap[0], &heap[nrElements], newHeap);
        delete[] heap;
        heap = newHeap;
        return 0;
    } catch (std::exception &e) {
        return -1;
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
    if (nrElements == heapCapacity) {
        if (resizeHeap() == -1) {
            cerr << "Error happened while allocating new Heap" << "\n";
            cerr << "New Item not added" << "\n";
            return;
        }
    }
    heap[nrElements] = data;
    upHeap(nrElements++);
}

int MinHeap::removeMin() {
    if (isEmpty()) return numeric_limits<int>::min();
    int min = heap[0];
    heap[0] = heap[--nrElements];
    downHeap(0);
    return min;
}

string MinHeap::toString() {
    string heapString;

    // Because a heap is filled from left to right
    // we can break early if a branch is not there
    for (int i = 0; i <= nrElements / 2; ++i) {
        heapString.append("Parent: " + to_string(heap[i]));

        const int leftChildIndex = leftChild(i);
        if (leftChildIndex == -1) break;

        heapString.append(", Left Child: " + to_string(heap[leftChildIndex]));

        const int rightChildIndex = rightChild(i);
        if (rightChildIndex == -1) break;

        heapString.append(", Right Child: " + to_string(heap[rightChildIndex]));
        heapString.append(";\n");
    }

    return heapString;
}

MinHeap::~MinHeap() {
    printf("MinHeap Destructor called");
    delete[] heap;
}

//struct HeapAllocError : public std::exception {
//    const char *what() const throw() {
//        return "Error happened while allocating new Heap";
//    }
//};
