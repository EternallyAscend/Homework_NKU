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
void sort(int *start,int *end,int length) {
	int i = 0;
	for (; i < length; i++) {
		int j = 0;
		for (; j < length - 1; j++) {
			if (start[j] > start[j + 1]) {
				int temp = start[j];
				start[j] = start[j + 1];
				start[j + 1] = temp;
				temp = end[j];
				end[j] = end[j + 1];
				end[j + 1] = temp;
			}
		}
	}
}

int main(void) {
	int n;
	scanf("%d", &n);
	int *rooms;
	int *start;
	int *end;
	int counter = 0;
	rooms = (int*)malloc(n * sizeof(int));
	start = (int*)malloc(n * sizeof(int));
	end = (int*)malloc(n * sizeof(int));
	int i;
	for (i = 0; i < n; i++) {
		rooms[i] = 0;
		scanf("%d %d", &start[i], &end[i]);
	}
	//sort(start, end, n);
	mergeSort(0, n, start, end);
	for (i = 0; i < n; i++) {
		int j = 0;
		for (; j < counter; j++) {
			if (rooms[j] <= start[i]) {
				//printf("Push\n");
				rooms[j] = end[i];
				break;
			}
		}
		if (j == counter) {
			//printf("New room\n");
			rooms[counter++]=end[i];
		}
	}
	printf("%d\n", counter);
	//system("pause");
	return 0;
}

/*
Problem description
Imagine：

There are N lectures, each with a fixed start and end time.
Each lecture needs a lecture hall.
There can only be one lecture in one lecture hall at the same time.
Two consecutive lectures are still allowed to take place in the same lecture hall if the start time of the second lecture is equal to the end time of the first one.
You are required to find the minimum number of lecture halls needed for scheduling all lectures.
Input
The first line is a positive integer N, indicating how many lectures to be scheduled.

Each of the next N lines has 2 positive integers, which represent the start time and end time of each lecture.

Time starts at 0.

Output
The output is the minimum number of lecture halls needed.

Hint
You'd like a schedule that minimizes the number of lecture halls needed. Use greedy algorithms to achieve that.



Annex

Sample of Input and Output
样例1
Input :
5
1 23
12 28
25 35
27 80
36 50
Output:
3
样例2
Input :
4
1 3
5 7
5 8
2 5
Output :
	2




Judgment Information:编译错误
判题日志:/judger/run/e8b11ae441864cc785744fdda4850dd5/main.cpp: In function 'void mergeSort(int, int, int*, int*)':
/judger/run/e8b11ae441864cc785744fdda4850dd5/main.cpp:38:19: error: invalid conversion from 'int*' to 'int' [-fpermissive]
temp[counter] = temp;
^
/judger/run/e8b11ae441864cc785744fdda4850dd5/main.cpp:39:26: error: invalid conversion from 'int*' to 'int' [-fpermissive]
tempOther[counter++] = tempOther;
^
/judger/run/e8b11ae441864cc785744fdda4850dd5/main.cpp:46:19: error: invalid conversion from 'int*' to 'int' [-fpermissive]
temp[counter] = temp;
^
compilation terminated due to -fmax-errors=3.
*/

