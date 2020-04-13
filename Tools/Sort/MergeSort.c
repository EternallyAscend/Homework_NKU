#pragma warning(disable:4996)

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>


void mergeSort(int start, int end, int *data) {
	if (start + 1 >= end) {
		return;
	}
	else {
		int middle = (int)((start + end) / 2);
		mergeSort(start, middle, data);
		mergeSort(middle, end, data);
		int leftCounter = start;
		int rightCounter = middle;
		int *temp = (int*)malloc((end - start) * sizeof(int));
		int counter = 0;
		while (leftCounter != middle && rightCounter != end) {
			int cache = data[leftCounter];
			if (data[leftCounter] > data[rightCounter]) {
				cache = data[rightCounter++];
			}
			else {
				leftCounter++;
			}
			temp[counter++] = cache;
		}
		if (leftCounter < middle) {
			while (leftCounter < middle) {
				temp[counter++] = data[leftCounter++];
			}
		}
		if (rightCounter < end) {
			while (rightCounter < end) {
				temp[counter] = data[rightCounter++];
			}
		}
		int i = start;
		for (; i < end; i++) {
			data[i] = temp[i - start];
		}
		free(temp);
	}
}
