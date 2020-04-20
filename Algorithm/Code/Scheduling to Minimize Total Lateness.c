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
int main(void) {
	int n;
	scanf("%d", &n);
	int time = 0;
	int current = 0;
	int *length;
	int *ddl;
	length = (int*)malloc(n * sizeof(int));
	ddl = (int*)malloc(n * sizeof(int));
	int i;
	for (i = 0; i < n; i++) {
		scanf("%d %d", &length[i], &ddl[i]);
	}
	mergeSort(0, n, ddl, length);
	for (i = 0; i < n; i++) {
		printf("%d %d\n", length[i], ddl[i]);
	}
	for (i = 0; i < n; i++) {
		current += length[i];
		time += current > ddl[i] ? current - ddl[i] : 0;
	}
	printf("%d\n", time);
	system("pause");
	return 0;
}
