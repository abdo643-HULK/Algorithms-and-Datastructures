//
// Created by Abdo on 08.11.21.
//

#ifndef UE3__QUICKSORT_MOT_PRIVATE_H_
#define UE3__QUICKSORT_MOT_PRIVATE_H_

#include <iostream>

int partition(int array[], int left, int right);
int calculatePivot(int array[], int left, int right) ;

/**
 * swaps 2 elements by dereferencing the pointers and
 * xoring them.
 *
 * @param a
 * @param b
 */
template<typename T>
void swap(T *a, T *b) {
	if (a == b) return;
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

#endif //UE3__QUICKSORT_MOT_PRIVATE_H_
