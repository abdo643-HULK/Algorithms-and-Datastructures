//
// Created by Abdo on 04.11.21.
//

#include "quicksort_mot.h"
#include "quicksort_mot_private.h"

/**
 * the functions to quicksort an array with the median of the outermost elements and the middle
 * as the pivot
 *
 * @param array the array to sort
 * @param size the size of the array
 * @param left the start of the search
 * @param right the end of the search
 */
void quicksort_mot(int array[], int size, int left, int right) {
	if (left >= right) return;

	const int q = partition(array, left, right);
	quicksort_mot(array, size, left, q - 1);
	quicksort_mot(array, size, q + 1, right);
}

/**
 *	partitions the array in 2 "arrays" by returning the index the
 *	recursion has to work with
 *
 * @param array
 * @param left start index of the search
 * @param right end index of the search
 * @return the index where the partition happens
 */
int partition(int array[], int left, int right) {
	const int pivot = calculatePivot(array, left, right);

	int i = left - 1;
	for (int j = left; j < right; ++j) {
		if (array[j] > pivot) continue;
		++i;
		swap(&array[i], &array[j]);
	}

	swap(&array[++i], &array[right]);
	return i;
}

/**
 * calculates the pivot by taking the median of the left and middle and end values of the array.
 * The calculated pivot gets switches position with the last right element, so we don't have to
 * work with different indices.
 *
 * @param array
 * @param left start index of the search
 * @param right end index of the search
 * @return the pivot element
 */
int calculatePivot(int array[], int left, int right) {
	const int middleIndex = (int) (right / 2);

	const int first = array[left];
	const int middle = array[middleIndex];
	const int last = array[right];

	if ((first > middle) ^ (first > last)) {
		const int pivot = first;
		array[left] = array[right];
		array[right] = pivot;
	} else if ((middle <= first) ^ (middle <= last)) {
		const int pivot = middle;
		array[middleIndex] = array[right];
		array[right] = pivot;
	}

	return array[right];
}