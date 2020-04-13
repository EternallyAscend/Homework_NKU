#pragma warning(disable:4996)

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

#pragma warning(disable:4996)

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>


void mergeSort(int start, int end, int *data, int *other) {
	if (start + 1 >= end) {
		return;
	}
	else {
		int middle = (int)((start + end) / 2);
		mergeSort(start, middle, data, other);
		mergeSort(middle, end, data, other);
		int leftCounter = start;
		int rightCounter = middle;
		int *temp = (int*)malloc((end - start) * sizeof(int));
		int *tempOther = (int*)malloc((end - start) * sizeof(int));
		int counter = 0;
		while (leftCounter != middle && rightCounter != end) {
			int cache = data[leftCounter];
			int cacheOther = other[leftCounter];
			if (data[leftCounter] > data[rightCounter]) {
				cache = data[rightCounter];
				cacheOther = other[rightCounter++];
			}
			else {
				leftCounter++;
			}
			temp[counter] = cache;
			tempOther[counter++] = cacheOther;
		}
		if (leftCounter < middle) {
			while (leftCounter < middle) {
				temp[counter] = data[leftCounter];
				tempOther[counter++] = other[leftCounter++];
			}
		}
		if (rightCounter < end) {
			while (rightCounter < end) {
				temp[counter] = data[rightCounter];
				tempOther[counter++] = other[rightCounter++];
			}
		}
		int i = start;
		for (; i < end; i++) {
			data[i] = temp[i - start];
			other[i] = tempOther[i - start];
		}
		free(temp);
		free(tempOther);
	}
}

/*
//Old Version
void mergeSort(int start, int end, int *data, int *other) {
	if (start + 1 >= end) {
		return;
	}
	else {
		int middle = (int)((start + end) / 2);
		mergeSort(start, middle, data, other);
		mergeSort(middle, end, data, other);
		int leftCounter = start;
		int rightCounter = middle;
		int *temp = (int*)malloc((end - start) * sizeof(int));
		int *tempOther = (int*)malloc((end - start) * sizeof(int));
		int counter = 0;
		while (leftCounter != middle && rightCounter != end) {
			int cache = data[leftCounter];
			int cacheOther = other[leftCounter];
			if (data[leftCounter] > data[rightCounter]) {
				cache = data[rightCounter];
				cacheOther = other[rightCounter++];
			}
			else {
				leftCounter++;
			}
			temp[counter] = cache;
			tempOther[counter++] = cacheOther;
		}
		if (leftCounter < middle) {
			while (leftCounter < middle) {
				int cache = data[leftCounter];
				int cacheOther = other[leftCounter++];
				temp[counter] = cache;
				tempOther[counter++] = cacheOther;
			}
		}
		if (rightCounter < end) {
			while (rightCounter < end) {
				int cache = data[rightCounter];
				int cacheOther = other[rightCounter++];
				temp[counter] = cache;
				tempOther[counter++] = cacheOther;
			}
		}
		int i = start;
		for (; i < end; i++) {
			data[i] = temp[i - start];
			other[i] = tempOther[i - start];
		}
		free(temp);
		free(tempOther);
	}
}
*/
