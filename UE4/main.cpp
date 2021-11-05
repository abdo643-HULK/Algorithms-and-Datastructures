#include <iostream>
#include "MinHeap.hpp"
#include "quicksort_mot.h"

using namespace std;

template<typename T>
void printArray(T array, int size) {
	const auto end = "\n";

	for (int i = 0; i < size - 1; ++i) {
		cout << array[i] << ", ";
	}

	cout << array[size - 1] << end;
}

int main() {
	//--------------------------------------//
	//--------------Aufgabe 1---------------//
	//--------------------------------------//

	MinHeap heap(20);

	heap.insert(5);
	heap.insert(3);
	heap.insert(19);
	heap.insert(10);
	heap.insert(88);
	heap.insert(16);
	heap.insert(6);
	heap.insert(22);
	heap.insert(8);

	std::cout << (heap.contains(4) ? "true" : "false") << "\n"; // false
	std::cout << (heap.contains(45) ? "true" : "false") << "\n"; // false

	std::cout << (heap.contains(88) ? "true" : "false") << "\n"; // true
	std::cout << (heap.contains(22) ? "true" : "false") << "\n"; // true
	std::cout << (heap.contains(10) ? "true" : "false") << "\n"; // true

	int arr[] = {15, 11, 14, 9, 7, 13, 10, 6, 8, 3, 1, 5, 12, 2, 4};
	const int arrSize = sizeof(arr) / sizeof(arr[0]);
	sort(arr, arrSize);
	printArray(arr, arrSize);

	//--------------------------------------//
	//--------------Aufgabe 2---------------//
	//--------------------------------------//

	int arr2[] = {15, 11, 14, 9, 7, 13, 10, 6, 8, 3, 1, 5, 12, 2, 4};
	const int arr2Size = sizeof(arr2) / sizeof(arr2[0]);
	quicksort_mot(arr2, arr2Size, 0, arr2Size - 1);
	printArray(arr2, arr2Size);

	int arr3[] = {10, 7, 8, 9, 1, 5};
	const int arr3Size = sizeof(arr3) / sizeof(arr3[0]);
	quicksort_mot(arr3, arr3Size, 0, arr3Size - 1);
	printArray(arr3, arr3Size);

	return 0;
}