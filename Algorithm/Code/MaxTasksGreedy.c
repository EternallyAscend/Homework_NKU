//#define_CRT_SECURE_NO_DEPRECATE

#pragma warning(disable:4996)

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

/*
3
5
1 2 4 6 8
3 5 7 9 10
*/


int main(void) {
	int length;
	scanf("%d", &length);
	int *start;
	int *end;
	start = (int*)malloc(length * sizeof(int));
	end = (int*)malloc(length * sizeof(int));
	int i = 0;
	for (i = 0; i < length; i++) {
		scanf("%d", &start[i]);
	}
	for (i = 0; i < length; i++) {
		scanf("%d", &end[i]);
	}
	int j = 0;
	for (i = 0; i < length; i++) {
		for (j = 0; j < length - 1; j++) {
			if (end[j] > end[j + 1]) {
				int temp = end[j];
				end[j] = end[j + 1];
				end[j + 1] = temp;
				temp = start[j];
				start[j] = start[j + 1];
				start[j + 1] = temp;
			}
		}
	}
	//end = mergeSort(0, length - 1, end);
	int Counter = 0;
	int CurrentTime = 0;
	for (i = 0; i < length; i++) {
		if (start[i] > CurrentTime) {
			Counter++;
			CurrentTime = end[i];
		}
	}
	printf("%d", Counter);
	free(start);
	free(end);
	return 0;
}

/*
int* mergeSort(int start, int end, int* data) {
	if (start == end) {
		return data;
	}
	else {
		int middle = (start + end) / 2;
		int *result = (int*)malloc((end - start + 1) * sizeof(int));
		//int *left = (int*)malloc((end - middle) * sizeof(int));
		//int *right = (int*)malloc((middle - start + 1) * sizeof(int));
		int *left = mergeSort(start, middle, data);
		int *right = mergeSort(middle + 1, end, data);
		int leftCounter = 0;
		int rightCounter = 1;
		int Counter = 0;
		for (Counter = 0; Counter <= end - start; Counter++) {
			result[Counter] = left[leftCounter] < right[rightCounter] ? left[leftCounter++] : right[rightCounter++];
			if (leftCounter == middle + 1 - start || rightCounter == end - middle) {
				break;
			}
		}
		if (leftCounter <= middle - start) {
			for (Counter; Counter <= end - start; Counter++) {
				result[Counter] = left[leftCounter++];
			}
		}
		else if (rightCounter < end - middle) {
			for (Counter; Counter <= end - start; Counter++) {
				result[Counter] = right[rightCounter++];
			}
		}
		return result;
	}
}

int main(void) {
	int length;
	scanf("%d", &length);
	int *start;
	int *end;
	start = (int*)malloc(length * sizeof(int));
	end = (int*)malloc(length * sizeof(int));
	int i = 0;
	for (i = 0; i < length; i++) {
		scanf("%d", &start[i]);
	}
	for (i = 0; i < length; i++) {
		scanf("%d", &end[i]);
	}
	int j = 0;
	for (i = 0; i < length; i++) {
		for (j = 0; j < length - 1; j++) {
			if (end[j] > end[j + 1]) {
				int temp = end[j];
				end[j] = end[j + 1];
				end[j + 1] = temp;
				temp = start[j];
				start[j] = start[j + 1];
				start[j + 1] = temp;
			}
		}
	}
	//end = mergeSort(0, length - 1, end);
	for (i = 0; i < length; i++) {
		printf("%d %d \n", start[i], end[i]);
	}
	int Counter = 0;
	int CurrentTime = 0;
	for (i = 0; i < length; i++) {
		if (start[i] > CurrentTime) {
			Counter++;
			CurrentTime = end[i];
		}
	}
	printf("%d", Counter);
	free(start);
	free(end);
	system("pause");
	return 0;
}
*/
