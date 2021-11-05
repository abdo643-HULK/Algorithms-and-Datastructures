//
// Created by Abdo on 28.10.21.
//

#ifndef UE3_MINHEAP_HPP
#define UE3_MINHEAP_HPP

#include <string>
#include <limits>
#include <algorithm>
#include <exception>
#include <iostream>

using namespace std;

// From rust and swift where all types
// don't have "_t"
using int8 = int8_t;
using int16 = int16_t;
using int32 = int32_t;
using int64 = int64_t;

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
	int contains(int value, int index_subtree);
	int8 resizeHeap();

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
	 * @param element - element to find in the heap
	 * @return returns true, if the heap contains element
	 */
	bool contains(int element);

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

/**
 * sorts the array elements using the MinHeap
 *
 * @param array array that will be sorted with the elements in descending order
 * @param sizeOfArray
 */
void sort(int array[], int sizeOfArray);

#endif //UE3_MINHEAP_HPP
