//
// Created by Abdo on 28.10.21.
//

#ifndef UE3_MINHEAP_HPP
#define UE3_MINHEAP_HPP

#include <string>
#include <limits>
#include <iterator>
#include <algorithm>


using namespace std;

class MinHeap {
private:
    int *heap;                  //Pointer to array representing the heap
    int nrElements;
    int heapCapacity;

    void upHeap(int index);

    void downHeap(int index);

    int parent(int index);

    int leftChild(int index);

    int rightChild(int index);

    void swap(int index1, int index2);

public:
    MinHeap(int initCapacity);

    /**
     * @return true if Heap is empty, false otherwise
     */
    bool isEmpty() const;

    /**
     * @return amount of elements in the Heap
     */
    int size() const;

    /**
    * @return minimum element, if the heap is empty std::numeric_limits<int>::min() is returned
    */
    int min() const;


    /**
     * inserts the `data` into the Heap
     *
     * @param data - element
     */
    void insert(int data);


    /**
     * removes and returns the minimum element
     *
     * @return the removed element
     */
    int removeMin();

    /**
     * @return string representation of the Heap
     */
    string toString();

    ~MinHeap();
};

#endif //UE3_MINHEAP_HPP
