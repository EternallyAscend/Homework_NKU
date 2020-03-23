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
�ж����򷽷�
Total number of submissions: 1071 timespassing number: 81 timesPassing rate: 7.56%

Memory limit: 134217728(BYTE)Time limit: 100000(MS)Input limit: 1000(ROWS)Output limit: 64(ROWS)

Problem description
���������ǵ����㷨����һ����������ݣ��𲽲��������������С�ÿ�������У��㷨������������ȡ��һԪ�أ���֮����������������ȷ��λ�á���˵���ֱ��ȫ��Ԫ������

�鲢����������µ������������Ƚ�ԭʼ���п���N��ֻ����1��Ԫ�ص����������У�Ȼ��ÿ�ε����鲢�������ڵ����������У�ֱ�����ֻʣ��1����������С�

�ָ���ԭʼ���к���ĳ�����㷨�������м����У������жϸ��㷨���������������㷨��

�����ʽ��

�����ڵ�һ�и���������N (<=100)�����һ�и���ԭʼ���е�N�����������һ�и�����ĳ�����㷨�������м����С�������������Ŀ���������������ּ��Կո�ָ���

�����ʽ��

�����ڵ�1���������Insertion Sort����ʾ�������򡢻�Merge Sort����ʾ�鲢����Ȼ���ڵ�2��������ø������㷨�ٵ���һ�ֵĽ�����С���Ŀ��֤ÿ����ԵĽ����Ψһ�ġ����ּ��Կո�ָ�������ĩ�����ж���ո�


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