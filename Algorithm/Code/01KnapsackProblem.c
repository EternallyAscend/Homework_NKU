#include<stdio.h>
#include<stdlib.h>
struct good{
	int weight;
	int volume;
};
int main(void) {
	int size;
	int n;
	scanf("%d %d", &size, &n);
	int i;
	int v;
	int w;
	struct good **list;
	list = (struct good**)malloc(n * sizeof(struct good*));
	for (i = 0; i < n; i++) {
		scanf("%d %d", &v, &w);
		list[i] = (struct good*)malloc(sizeof(struct good));
		list[i]->volume = v;
		list[i]->weight = w;
	}
	int **result;
	result = (int**)malloc(n * sizeof(int*));
	int j;
	for (i = 0; i < n; i++) {
		result[i] = (int*)malloc(size * sizeof(int));
		for (j = 0; j < size; j++) {
			result[i][j] = 0;
		}
	}
	for (i = 0; i < size; i++) {
		if (list[0]->volume <= i + 1) {
			result[0][i] = list[0]->weight;
		}
	}
	for (i = 0; i < size; i++) {
		for (j = 1; j < n; j++) {
			if (i + 1 < list[j]->volume) {
				result[j][i] = result[j - 1][i];
			}
			else {
				int a;
				if (i < list[j]->volume) {
					a = list[j]->weight;
				}
				else {
					a = result[j - 1][i - list[j]->volume] + list[j]->weight;
				}
				result[j][i] = a > result[j - 1][i] ? a : result[j - 1][i];
			}
		}
	}
	printf("%d\n", result[n - 1][size - 1]);
	for (i = 0; i < n; i++) {
		free(result[i]);
		free(list[i]);
	}
	free(result);
	free(list);
	return 0;
}

/*
Problem description
Given the weights and values of `n` items, put these items in a knapsack with the capacity `W`.  You should find a way to maximize the total value of the items put into the knapsack.

Specifically, you will be given two integer arrays `val[0..n-1]` and `wt[0..n-1]` which represent the values and weights of `n` items, respectively, and an integer `W` which denotes the knapsack's capacity. You should find the subset of items achieving maximum sum of values. Recall that the sum of the weights of these items is smaller than or equal to `W`.

You cannot break an item, and should either pick the whole item or do not pick it (0-1 property).

Input
The first line has two positive integers `W` (`W` ≤ 200) and `n` (`n` ≤ 30), indicating the capacity of the knapsack as well as the number of items, respectively. Each of the next `n` lines has 2 integers, which respectively denote the weight and value of each item.

Output
The output is the maximum sum of the value of the items put into the knapsack.



Annex

Sample of Input and Output
1
Input:
10 4 
2 1 
3 3 
4 5 
7 9
Output:
12
*/
