#pragma warning(disable:4996)
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
int findNext(int element,int *list,int length,int start) {
	int i = start;
	for (; i < length; i++) {
		//printf("element : %d , list[i] : %d\n",element,list[i]);
		if (list[i] == element) {
			return i;
		}
	}
	return length + 1;
}
int getMax(int *list, int length) {
	int i = 0;
	int pos = 0;
	int max = list[0];
	for (; i < length; i++) {
		if (list[i] > max) {
			pos = i;
			max = list[i];
		}
	}
	return pos;
}
int mainC(void) {
	int cacheSize;
	int inputSize;
	scanf("%d %d", &inputSize, &cacheSize);
	if (cacheSize > inputSize) {
		cacheSize = inputSize;
	}
	int cacheCounter = 0;
	int *cachePool = (int*)malloc(cacheSize * sizeof(int));
	int *nextPool = (int*)malloc(cacheSize * sizeof(int));
	int cursor = 0;
	int reader = 0;
	int writer = 0;
	int *inputList = (int*)malloc(inputSize * sizeof(int));
	int pushTime = 0;
	for (writer; writer < inputSize; writer++) {
		scanf("%d", &inputList[writer]);
	}
	for (writer = 0; writer < inputSize; writer++) {
		if (cacheCounter < cacheSize) {
			reader = 0;
			for (cursor = 0; cursor < cacheCounter; cursor++) {
				if (cachePool[cursor] == inputList[writer]) {
					reader = 1;
					nextPool[cursor] = findNext(inputList[writer], inputList, inputSize, writer + 1);
					break;
				}
			}
			if (reader == 0) {
				cachePool[cacheCounter] = inputList[writer];
				nextPool[cacheCounter++] = findNext(inputList[writer], inputList, inputSize, writer + 1);
				pushTime++;
			}
		}
		else {
			reader = 0;
			for (cursor = 0; cursor < cacheSize; cursor++) {
				if (cachePool[cursor] == inputList[writer]) {
					reader = 1;
					nextPool[cursor] = findNext(inputList[writer], inputList, inputSize, writer + 1);
					break;
				}
			}
			if (reader == 0) {
				int pos = getMax(nextPool, cacheSize);
				cachePool[pos] = inputList[writer];
				nextPool[pos] = findNext(inputList[writer], inputList, inputSize, writer + 1);
				pushTime++;
			}
		}
		/*
		printf("\n Cache -- ");
		for (cursor = 0; cursor < cacheSize; cursor++) {
			printf("%d ", cachePool[cursor]);
		}
		printf("\n NextN -- ");
		for (cursor = 0; cursor < cacheSize; cursor++) {
			printf("%d ", nextPool[cursor]);
		}
		printf("\n");
		*/
	}
	printf("%d", pushTime);
	free(cachePool);
	free(nextPool);
	free(inputList);
	system("pause");
	return 0;
}
