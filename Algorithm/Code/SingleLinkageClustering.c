/*
Single-linkage Clustering
Total number of submissions: 2 timespassing number: 2 timesPassing rate: 100.00%

Memory limit: 268435456(BYTE)Time limit: 1000(MS)Input limit: 1000(ROWS)Output limit: 1000(ROWS)

Problem description
You are given n nodes in a two-dimensional space. 
You want to use single-linkage clustering method to find k clusters. 
This is equivalent to finding an MST (Minimum Spanning Tree) 
of these nodes and deleting k-1 longest edges. Your job is to 
output the length of the (k-1)-th longest edge of the MST.


Input
There are multiple cases. For each case, the first line 
has two integers n and k (2<=k<=n<=100). The following 
n lines give the coordinates of n nodes. You may use 
Euclidean distance to measure the distance between two nodes. 
All coordinates are integers.

Output
For each case, output the length of the (k-1)-th longest edge of the MST. 
The precision is set to 2 digits after the decimal point.

Annex

Sample of Input and Output
样例1
Input:
6 2
1 1
2 1
1 2
3 3
4 2
4 3
Output:
2.24

*/
#pragma warning(disable:4996)
#include<math.h>
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

struct map {
	int size;
	int tail;
	double* distance;
	int* position;
	int* endPoint;
	short* unreached;
	double* minHeap;
	int minHeapTail;
	int reached;
};

void initMap(struct map* Map, int Size) {
	Map->size = Size;
	Map->tail = 0;
	Map->distance = (double*)malloc((((Size - 1)*Size) >> 1) * sizeof(double));
	Map->position = (int*)malloc((Size << 1) * sizeof(int));
	Map->endPoint = (int*)malloc((Size - 1)*Size * sizeof(int));
	Map->unreached = (short*)malloc(Size * sizeof(short));
	Map->minHeap = (double*)malloc((((Size - 1)*Size) >> 1) * sizeof(double));
	int i;
	int j;
	int cursor;
	cursor = 0;
	for (i = 0; i < Size; i++) {
		Map->unreached[i] = -1; // Here -1 means unreached, other means group id.
		for (j = 0; j < i; j++) {
			Map->endPoint[cursor++] = j;
			Map->endPoint[cursor++] = i;
		}
	}
}

void displayMap(struct map* Map) {
	int i;
	for (i = 0; i < Map->tail; i++) {
		printf("x=%d\t y=%d\n", Map->position[i << 1], Map->position[(i << 1) + 1]);
	}
	int cursor;
	cursor = ((Map->tail - 1)*(Map->tail)) >> 1;
	for (i = 0; i < cursor; i++) {
		printf("Distance %d %.2f\n", i, Map->distance[i]);
	}
	for (i = 0; i < cursor; i++) {
		printf("Left=%d Right=%d\n", Map->endPoint[i << 1], Map->endPoint[(i << 1) + 1]);
	}
}

void delMap(struct map* Map) {
	free(Map->distance);
	free(Map->position);
	free(Map->endPoint);
	free(Map->unreached);
	free(Map->minHeap);
}

void insertMap(struct map* Map, int x, int y) {
	if (Map->tail == Map->size) {
		return;
	}
	int i;
	int cursor;
	cursor = ((Map->tail - 1)*Map->tail) >> 1;
	for (i = 0; i < Map->tail; i++) {
		Map->distance[cursor++] = sqrt((double)((x - Map->position[i << 1])*(x - Map->position[i << 1]) + (y - Map->position[1 + (i << 1)])*(y - Map->position[1 + (i << 1)])));
	}
	Map->position[Map->tail << 1] = x;
	Map->position[(Map->tail++ << 1) + 1] = y;
}

void exchangeInMap(struct map* Map, int left, int right) {
	int temp;
	double cache;
	cache = Map->minHeap[left];
	Map->minHeap[left] = Map->minHeap[right];
	Map->minHeap[right] = cache;
	temp = Map->endPoint[left << 1];
	Map->endPoint[left << 1] = Map->endPoint[right << 1];
	Map->endPoint[right << 1] = temp;
	temp = Map->endPoint[1 + (left << 1)];
	Map->endPoint[1 + (left << 1)] = Map->endPoint[1 + (right << 1)];
	Map->endPoint[1 + (right << 1)] = temp;
}


void addjustToMinHeap(struct map* Map) {
	Map->reached = 0;
	int i;
	Map->minHeapTail = 1;
	int length = (((Map->size - 1)*Map->size) >> 1);
	Map->minHeap[0] = Map->distance[0];
	int cursor;
	for (i = 1; i < length; i++) {
		cursor = Map->minHeapTail;
		Map->minHeap[Map->minHeapTail++] = Map->distance[i];
		while (cursor != 0) {
			if (Map->minHeap[cursor] >= Map->minHeap[(int)((cursor - 1) >> 1)]) {
				break;
			}
			exchangeInMap(Map, cursor, (int)((cursor - 1) >> 1));
			cursor = (int)((cursor - 1) >> 1);
		}
	}
}

double delNodeInMapMinHeap(struct map* Map, int position) {
	if (position >= Map->minHeapTail) {
		return -1;
	}
	int cursor;
	cursor = --Map->minHeapTail;
	exchangeInMap(Map, position, cursor);
	cursor = position;
	while (cursor < Map->minHeapTail) {
		if ((1 + (cursor << 1)) < Map->minHeapTail) {
			double left;
			left = Map->minHeap[1 + (cursor << 1)];
			if ((2 + (cursor << 1)) < Map->minHeapTail) {
				double right;
				right = Map->minHeap[2 + (cursor << 1)];
				if (left < right) {
					if (Map->minHeap[cursor] > left) {
						exchangeInMap(Map, cursor, 1 + (cursor << 1));
						cursor = 1 + (cursor << 1);
					}
					else {
						break;
					}
				}
				else {
					if (Map->minHeap[cursor] > right) {
						exchangeInMap(Map, cursor, 2 + (cursor << 1));
						cursor = 2 + (cursor << 1);
					}
					else {
						break;
					}
				}
			}
			else {
				if (Map->minHeap[cursor] > left) {
					exchangeInMap(Map, cursor, 1 + (cursor << 1));
				}
				break;
			}
		}
		else {
			break;
		}
	}
	return Map->minHeap[Map->minHeapTail];
}

void group(struct map* Map, int left, int right) {
	if (Map->unreached[right] == -1) {
		if (Map->unreached[left] == -1) {
			Map->unreached[right] = right;
			Map->unreached[left] = right;
			Map->reached++;
		}
		else {
			Map->unreached[right] = Map->unreached[left];
			Map->reached++;
		}
	}
	else {
		if (Map->unreached[left] == -1) {
			Map->unreached[left] = Map->unreached[right];
			Map->reached++;
		}
		else {
			int leftRoot;
			int rightRoot;
			leftRoot = left;
			rightRoot = right;
			int leftCounter;
			int rightCounter;
			leftCounter = 0;
			rightCounter = 0;
			while (leftRoot != Map->unreached[leftRoot]) {
				leftRoot = Map->unreached[leftRoot];
				leftCounter++;
			}
			while (rightRoot != Map->unreached[rightRoot]) {
				rightRoot = Map->unreached[rightRoot];
				rightCounter++;
			}
			if (leftRoot == rightRoot) {
				return;
			}
			if (leftCounter >= rightCounter) {
				Map->unreached[leftRoot] = rightRoot;
			}
			else {
				Map->unreached[rightRoot] = leftRoot;
			}
			Map->reached++;
		}
	}
}


double pop(struct map* Map) {
	if (Map->minHeapTail == 0) {
		return -1;
	}
	group(Map, Map->endPoint[0], Map->endPoint[1]);
	return delNodeInMapMinHeap(Map, 0);
}

double getK(struct map* Map, int k) {
	addjustToMinHeap(Map);
	double length;
	length = 0;
	int reach;
	reach = 0;
	while (reach != Map->size - k + 1) {
		length = pop(Map);
		reach = Map->reached;
		if (length == -1) {
			break;
		}
	}
	return length;
}

int main(void) {
	int n;
	int k;
	while (scanf("%d", &n) == 1) {
		scanf("%d", &k);
		int x;
		int y;
		struct map Map;
		initMap(&Map, n);
		int i;
		for (i = 0; i < n; i++) {
			scanf("%d %d", &x, &y);
			insertMap(&Map, x, y);
		}
		double result;
		result = getK(&Map, k);
		printf("%.2f", result);
		delMap(&Map);
	}
	system("pause");
	return 0;
}
/*
#pragma warning(disable:4996)
#include<math.h>
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

struct minHeap {
	int size;
	int tail;
	double* length;
};

struct map {
	int size;
	int tail;
	double* distance;
	int* position;
	int* endPoint;
	short* unreached;
	double* minHeap;
	int minHeapTail;
	int reached;
};

void initMap(struct map* Map, int Size) {
	Map->size = Size;
	Map->tail = 0;
	Map->distance = (double*)malloc((((Size - 1)*Size) >> 1) * sizeof(double));
	Map->position = (int*)malloc((Size << 1) * sizeof(int));
	Map->endPoint = (int*)malloc((Size - 1)*Size * sizeof(int));
	Map->unreached = (short*)malloc(Size * sizeof(short));
	Map->minHeap = (double*)malloc((((Size - 1)*Size) >> 1) * sizeof(double));
	int i;
	int j;
	int cursor;
	cursor = 0;
	for (i = 0; i < Size; i++) {
		Map->unreached[i] = -1;// Here -1 means unreached, other means group id.
		for (j = 0; j < i; j++) {
			Map->endPoint[cursor++] = j;
			Map->endPoint[cursor++] = i;
		}
	}
}

void displayMap(struct map* Map) {
	int i;
	for (i = 0; i < Map->tail; i++) {
		printf("x=%d\t y=%d\n", Map->position[i << 1], Map->position[(i << 1) + 1]);
	}
	int cursor;
	cursor = ((Map->tail - 1)*(Map->tail)) >> 1;
	for (i = 0; i < cursor; i++) {
		printf("Distance %d %.2f\n", i, Map->distance[i]);
	}
	for (i = 0; i < cursor; i++) {
		printf("Left=%d Right=%d\n", Map->endPoint[i << 1], Map->endPoint[(i << 1) + 1]);
	}
}

void delMap(struct map* Map) {
	free(Map->distance);
	free(Map->position);
	free(Map->endPoint);
	free(Map->unreached);
	free(Map->minHeap);
}

void insertMap(struct map* Map, int x, int y) {
	if (Map->tail == Map->size) {
		return;
	}
	int i;
	int cursor;
	cursor = ((Map->tail - 1)*Map->tail) >> 1;
	for (i = 0; i < Map->tail; i++) {
		Map->distance[cursor++] = sqrt((double)((x - Map->position[i << 1])*(x - Map->position[i << 1]) + (y - Map->position[1 + (i << 1)])*(y - Map->position[1 + (i << 1)])));
	}
	Map->position[Map->tail << 1] = x;
	Map->position[(Map->tail++ << 1) + 1] = y;
}

void exchangeInMap(struct map* Map, int left, int right) {
	int temp;
	double cache;
	cache = Map->minHeap[left];
	Map->minHeap[left] = Map->minHeap[right];
	Map->minHeap[right] = cache;
	temp = Map->endPoint[left << 1];
	Map->endPoint[left << 1] = Map->endPoint[right << 1];
	Map->endPoint[right << 1] = temp;
	temp = Map->endPoint[1 + (left << 1)];
	Map->endPoint[1 + (left << 1)] = Map->endPoint[1 + (right << 1)];
	Map->endPoint[1 + (right << 1)] = temp;
}


void addjustToMinHeap(struct map* Map) {
	Map->reached = 0;
	int i;
	Map->minHeapTail = 1;
	int length = (((Map->size - 1)*Map->size) >> 1);
	Map->minHeap[0] = Map->distance[0];
	int cursor;
	for (i = 1; i < length; i++) {
		cursor = Map->minHeapTail;
		Map->minHeap[Map->minHeapTail++] = Map->distance[i];
		while (cursor != 0) {
			if (Map->minHeap[cursor] >= Map->minHeap[(int)((cursor - 1) >> 1)]) {
				break;
			}
			exchangeInMap(Map, cursor, (int)((cursor - 1) >> 1));
			cursor = (int)((cursor - 1) >> 1);
		}
	}
}

double delNodeInMapMinHeap(struct map* Map, int position) {
	if (position >= Map->minHeapTail) {
		return -1;
	}
	int cursor;
	cursor = --Map->minHeapTail;
	exchangeInMap(Map, position, cursor);
	cursor = position;
	while (cursor < Map->minHeapTail) {
		double left;
		double right;
		left = -1;
		right = -1;
		if (2 + (cursor << 1) < Map->minHeapTail) {
			left = Map->minHeap[(cursor << 1) + 1];
			right = Map->minHeap[(cursor << 1) + 2];
			if (left < right) {
				if (Map->minHeap[cursor] > left) {
					exchangeInMap(Map, cursor, 1 + (cursor << 1));
					cursor = 1 + (cursor << 1);
				}
				else {
					break;
				}
			}
			else {
				if (Map->minHeap[cursor] > right) {
					exchangeInMap(Map, cursor, 2 + (cursor << 1));
					cursor = 2 + (cursor << 1);
				}
				else {
					break;
				}
			}
		}
		else if (1 + (cursor << 1) < Map->minHeapTail) {
			left = Map->minHeap[(cursor << 1) + 1];
			if (Map->minHeap[cursor] > left) {
				exchangeInMap(Map, cursor, 1 + (cursor << 1));
				cursor = 1 + (cursor << 1);
			}
			else {
				break;
			}
		}
		else {
			break;
		}
	}
	return Map->minHeap[Map->minHeapTail];
}

void group(struct map* Map, int left, int right) {
	if (Map->unreached[right] == -1) {
		if (Map->unreached[left] == -1) {
			Map->unreached[right] = right;
			Map->unreached[left] = right;
			Map->reached++;
		}
		else {
			Map->unreached[right] = Map->unreached[left];
			Map->reached++;
		}
	}
	else {
		if (Map->unreached[left] == -1) {
			Map->unreached[left] = Map->unreached[right];
			Map->reached++;
		}
		else {
			int leftRoot;
			int rightRoot;
			leftRoot = left;
			rightRoot = right;
			int leftCounter;
			int rightCounter;
			leftCounter = 0;
			rightCounter = 0;
			while (leftRoot != Map->unreached[leftRoot]) {
				leftRoot = Map->unreached[leftRoot];
				leftCounter++;
			}
			while (rightRoot != Map->unreached[rightRoot]) {
				rightRoot = Map->unreached[rightRoot];
				rightCounter++;
			}
			if (leftRoot == rightRoot) {
				return;
			}
			if (leftCounter >= rightCounter) {
				Map->unreached[leftRoot] = rightRoot;
			}
			else {
				Map->unreached[rightRoot] = leftRoot;
			}
			Map->reached++;
		}
	}
}


double pop(struct map* Map) {
	if (Map->minHeapTail == 0) {
		return -1;
	}
	group(Map, Map->endPoint[0], Map->endPoint[1]);
	return delNodeInMapMinHeap(Map, 0);
}

double getK(struct map* Map, int k) {
	addjustToMinHeap(Map);
	double length;
	length = 0;
	int reach;
	reach = 0;
	while (reach != Map->size - k + 1) {
		length = pop(Map);
		reach = Map->reached;
		if (length == -1) {
			break;
		}
	}
	return length;
}

int main(void) {
	int n;
	int k;
	while (scanf("%d", &n) == 1) {
		scanf("%d", &k);
		int x;
		int y;
		struct map Map;
		initMap(&Map, n);
		int i;
		for (i = 0; i < n; i++) {
			scanf("%d %d", &x, &y);
			insertMap(&Map, x, y);
		}
		double result;
		result = getK(&Map, k);
		printf("%.2f\n", result);
		delMap(&Map);
	}
	return 0;
}
*/
