//
// Created by Abdo on 04.11.21.
//

#include "quicksort_mot.h"

int partition(int array[], int size, int left, int right);
int calculatePivot(int array[], int left, int right) ;
void swap(int *a, int *b);

void quicksort_mot(int array[], int size, int left, int right) {
	if (left >= right) return;

	const int q = partition(array, size, left, right);
	quicksort_mot(array, size, left, q - 1);
	quicksort_mot(array, size, q + 1, right);
}

int partition(int array[], int size, int left, int right) {
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

void swap(int *a, int *b) {
	if (a == b) return;
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;

//	int temp = *a;
//	*a = *b;
//	*b = temp;
}

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