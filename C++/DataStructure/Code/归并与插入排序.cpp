#include<iostream>
#include<vector>
using namespace std;
void insertionSort(vector<int> &data,vector<int> &ink) {
	bool goOut = false;
	for (int i = 0; i < data.size(); i++) {
		bool check = false;
		int j;
		for(j=0;j<i;j++){
			if ((data)[i] < (data)[j]) {
			check = true;
			break;
			}
		}
		if (check) {
			int temp = (data)[i];
			for (int k = i; k > j; k--) {
				(data)[k] = (data)[k - 1];
			}
			(data)[j] = temp;
		}
		if (goOut) {
			cout << "Insertion Sort" << endl;
			for (int k = 0; k < (data).size() - 1; k++) { cout << (data)[k] << " "; }
			cout << (data)[data.size()-1] << endl;
			return;
		}
		if ((data) == (ink)) { goOut = true; }
	}

}
void mergeSort(vector<int> &data,int head,int tail) {
	if (head == tail) { return; }
	int middle = (head + tail) / 2;
	mergeSort(data, head, middle);
	mergeSort(data, middle + 1, tail);
	for (int i = head; i < tail; i++) {
		bool check = false;
		int j;
		for (j = head; j < i; j++) {
			if((data)[j]>(data)[i]){
				check = true;
				break;
			}
		}
		if (check) {
			int temp = (data)[i];
			for (int k = i; k > j; k--) {
				(data)[k] = (data)[k - 1];
			}
			(data)[j] = temp;
		}
	}
}
void merge(vector<int> &x, vector<int> &y, int start, int endst, int endrd) {
	int middle = endst + 1;
	int tail = start;
	while ((start <= endst) && (middle <= endrd)) {
		if (x[start] <= x[middle]) { y[tail++] = x[start++]; }
		else y[tail++] = x[middle++];
	}
	if (start < endst + 1) {
		for (start; start <= endst; start++) { y[tail++] = x[start]; }
	}
	else {
		for (middle; middle <= endrd; middle++) { y[tail++] = x[middle]; }
	}
}
void mergePass(vector<int> &x,vector<int> &y,int size) {
	int i = 0;
	while (i < (int)x.size() - 2 * size) {
		merge(x, y, i, i + size - 1, i + 2 * size - 1);
		i += 2 * size;
	}
	if (i + size < x.size()) {
		merge(x, y, i, i + size - 1, x.size() - 1);

	}
	else {
		for (i; i < x.size(); i++) { y[i] = x[i]; }
	}
}
void mergeSort(vector<int> &data,vector<int> &ink) {
	vector<int> cache;
	for (int i = 0; i < data.size(); i++) { cache.push_back(data[i]); }
	int size = 1;
	bool inData, inCache;
	inData = inCache = false;
	while (size < data.size()) {
		if (data == ink) { inData = true; }
		mergePass(data, cache, size);
		size *= 2;
		if (inData) {
			cout << "Merge Sort" << endl;
			for (int i = 0; i < cache.size() - 1; i++) { cout << cache[i]<<" "; }
			cout << cache[cache.size() - 1] << endl;
			return;
		}
		if (cache == ink) { inCache = true; }
		if (size >= data.size()) break;
		mergePass(cache, data, size);
		size *= 2;
		if (inCache) {
			cout << "Merge Sort" << endl;
			for (int i = 0; i < data.size() - 1; i++) { cout << data[i] << " "; }
			cout << data[data.size() - 1] << endl;
			return;
		}
	}
}
void which(vector<int> &data,vector<int> ink) {
	vector<int> test1, test0;
	for (int i = 0; i < data.size(); i++) {
		test1.push_back(data[i]);
		test0.push_back(data[i]);
	}
	insertionSort(test1, ink);
	//mergeSort(test0, 0, data.size());
	mergeSort(test0, ink);
}
int main(void) {
	vector<int> data;
	vector<int> temp;
	int n,cache;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> cache;
		data.push_back(cache); 
	}
	for (int i = 0; i < n; i++) {
		cin >> cache;
		temp.push_back(cache);
	}
	which(data, temp);
	//insertionSort(data, temp);
	//mergeSort(data, 0, data.size());
	system("pause");
	return 0;
}

/*
判断排序方法
Total number of submissions: 1071 timespassing number: 81 timesPassing rate: 7.56%

Memory limit: 134217728(BYTE)Time limit: 100000(MS)Input limit: 1000(ROWS)Output limit: 64(ROWS)

Problem description
插入排序是迭代算法，逐一获得输入数据，逐步产生有序的输出序列。每步迭代中，算法从输入序列中取出一元素，将之插入有序序列中正确的位置。如此迭代直到全部元素有序。

归并排序进行如下迭代操作：首先将原始序列看成N个只包含1个元素的有序子序列，然后每次迭代归并两个相邻的有序子序列，直到最后只剩下1个有序的序列。

现给定原始序列和由某排序算法产生的中间序列，请你判断该算法究竟是哪种排序算法？

输入格式：

输入在第一行给出正整数N (<=100)；随后一行给出原始序列的N个整数；最后一行给出由某排序算法产生的中间序列。这里假设排序的目标序列是升序。数字间以空格分隔。

输出格式：

首先在第1行中输出“Insertion Sort”表示插入排序、或“Merge Sort”表示归并排序；然后在第2行中输出用该排序算法再迭代一轮的结果序列。题目保证每组测试的结果是唯一的。数字间以空格分隔，且行末不得有多余空格。


Annex

Sample of Input and Output
InsertionSort
Input:
10
3 1 2 8 7 5 9 4 6 0
1 2 3 7 8 5 9 4 6 0
Output:
Insertion Sort
1 2 3 5 7 8 9 4 6 0
MergeSort
Input:
10
3 1 2 8 7 5 9 4 0 6
1 3 2 8 5 7 4 9 0 6
Output:
Merge Sort
1 2 3 8 4 5 7 9 0 6
*/