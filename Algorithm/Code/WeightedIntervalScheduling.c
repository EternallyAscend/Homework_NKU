#pragma warning(disable:4996)

#include<stdio.h>
#include<stdlib.h>

struct task {
	int start;
	int end;
	int weight;
};

void assign(struct task* left, struct task* right) {
	left->start = right->start;
	left->end = right->end;
	left->weight = right->weight;
}

void mergeSort(int start,int end,struct task** list) {
	if (start + 1 >= end) {
		return;
	}
	int middle = (int)((start + end) / 2);
	mergeSort(start, middle, list);
	mergeSort(middle, end, list);
	int i;
	int leftCounter;
	int rightCounter;
	leftCounter = start;
	rightCounter = middle;
	struct task** temp;
	temp = (struct task**)malloc((end - start) * sizeof(struct task*));
	i = 0;
	while (leftCounter < middle&&rightCounter < end) {
		temp[i] = (struct task*)malloc(sizeof(struct task));
		if (list[leftCounter]->end > list[rightCounter]->end) {
			assign(temp[i++], list[rightCounter++]);
		}
		else {
			assign(temp[i++], list[leftCounter++]);
		}
	}
	int counter;
	if (leftCounter == middle) {
		counter = rightCounter;
	}
	else if (rightCounter == end) {
		counter = leftCounter;
	}
	while (i < end - start) {
		temp[i] = (struct task*)malloc(sizeof(struct task));
		assign(temp[i++], list[counter++]);
	}
	for (i = start; i < end; i++) {
		assign(list[i], temp[i - start]);
		free(temp[i - start]);
	}
	free(temp);
}

int binaryFindFront(int left, int right, int position, struct task** list) {
	int middle;
	while (left < right - 1) {
		middle = (int)((left + right) / 2);
		if (list[middle]->end > list[position]->start) {
			right = middle;
		}
		else {
			left = middle;
		}
	}
	return left;
}

void getFront(int length, int* front, struct task** list) {
	int i;
	front[0] = -1;
	for (i = length - 1; i > 0; i--) {
		if (list[i]->start < list[0]->end) {
			front[i] = -1;
		}
		else {
			front[i] = binaryFindFront(0, i, i, list);
		}
	}
}

int getDPN(int length, int* maxlist, int *front, struct task** list) {
	int i;
	maxlist[0] = list[0]->weight;
	for (i = 1; i < length; i++) {
		if (front[i] == -1) {
			maxlist[i] = (maxlist[i - 1] > list[i]->weight) ? maxlist[i - 1] : list[i]->weight;
		}
		else {
			maxlist[i] = (maxlist[i - 1] > maxlist[front[i]] + list[i]->weight) ? maxlist[i - 1] : maxlist[front[i]] + list[i]->weight;
		}
	}
	return maxlist[length - 1];
}

void display(int n, struct task** list) {
	int i;
	printf("\n");
	for (i = 0; i < n; i++) {
		printf("%d ", list[i]->start);
	}
	printf("\n");
	for (i = 0; i < n; i++) {
		printf("%d ", list[i]->end);
	}
	printf("\n");
	for (i = 0; i < n; i++) {
		printf("%d ", list[i]->weight);
	}
	printf("\n");
}


int main(void) {
	int n;
	scanf("%d", &n);
	struct task** list;
	list = (struct task**)malloc(n * sizeof(struct task*));
	int start;
	int end;
	int weight;
	int i;
	int* maxlist;
	maxlist = (int*)malloc(n * sizeof(int));
	int* front;
	front = (int*)malloc(n * sizeof(int));
	for (i = 0; i < n; i++) {
		maxlist[i] = 0;
		front[i] = 0;
		scanf("%d %d %d", &start, &end, &weight);
		list[i] = (struct task*)malloc(sizeof(struct task));
		list[i]->start = start;
		list[i]->end = end;
		list[i]->weight = weight;
	}
	mergeSort(0, n, list);
	getFront(n, front, list);
	printf("%d\n", getDPN(n, maxlist, front, list));
	for (i = 0; i < n; i++) {
		printf("%d ", front[i]);
	}
	for (i = 0; i < n; i++) {
		free(list[i]);
	}
	free(list);
	free(front);
	free(maxlist);
	system("pause");
	return 0;
}


	/*
	struct task* a;
	struct task* b;
	a = (struct task*)malloc(sizeof(struct task));
	b = (struct task*)malloc(sizeof(struct task));
	a->end = 0;
	a->start = 0;
	a->weight = 0;
	b->end = 1;
	b->start = 2;
	b->weight = 3;
	printf("%d %d %d\n", a->start, a->end, a->weight);
	printf("%d %d %d\n", b->start, b->end, b->weight);
	assign(a, b);
	printf("%d %d %d\n", a->start, a->end, a->weight);
	printf("%d %d %d\n", b->start, b->end, b->weight);

	system("pause");
	*/


/*
Weighted Interval Scheduling
Total number of submissions: 7 timespassing number: 5 timesPassing rate: 71.43%

Memory limit: 33554432(BYTE)Time limit: 1000(MS)Input limit: 1000(ROWS)Output limit: 1000(ROWS)

Problem description
You are given n jobs where every job is represented by the following three attributes.

Start Time
End Time
Profit or Value Associated (>= 0)
You need to find the maximum profit subset of jobs such that no two jobs in the subset overlap.

Example
Job 1: {1, 3, 10}
Job 2: {2, 4, 100}
Job 3: {3, 5, 20}
Job 4: {5, 6, 30}
We can get the maximum profit by scheduling Job 2, 4. The maximum profit is 130.

Note that there is a longer schedule possible for Job 1, 3 and 4, but the profit with this schedule is 10+20+30=60 which is less than 130.

Input
The first line is a positive integer n (n<1000), indicating how many jobs to be scheduled.

Each of the next n lines has 3 integers, which represent the start time, end time and the profit of each job, respectively.

Time starts at 0.

Output
The output is the maximum profit possible.

Hint
Use binary search to get the optimal time complexity.

Annex

Sample of Input and Output
样例1
Input:
4
1 3 10
2 4 100
3 5 20
5 6 30
Output:
130

Input:
5
1 3 20
2 5 20
3 10 100
4 6 70
6 9 60
Output:
150


4
5 6 30
3 5 20
2 4 100
1 3 10
*/


/*
//输入
intN, S[MAX_N], T[MAX_N];
//用于对工作排序的pair数组
pair<int, int>itv[MAX_N];
voidsolve()
{
	//对pair进行的是字典序比较，为了让结束时间早的工作排在前面，把T存入first，//把S存入second
	for (inti = 0; i < N; i++)
	{
		itv[i].first = T[i];
		itv[i].second = S[i];
	}
	sort(itv, itv + N);
	dp[0] = (itv[0].first - itv[0].second)*V[0];
	for (inti = 1; i < N; i++)
	{
		intmax;
		//select the ithinterval
		intnonOverlap = lower_bound(itv, itv[i].second) - 1;
		if (nonOverlap >= 0)
			max = dp[nonOverlap] + (itv[i].first - itv[i].second)*V[i];
		else
			max = (itv[i].first - itv[i].second)*V[i];
		//do not selectthe ith interval
		dp[i] = max > dp[i - 1] ? max : dp[i - 1];
	}
	printf(“%d\n”, dp[N - 1]);
}
*/
