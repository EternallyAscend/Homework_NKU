#include<iostream>
using namespace std;
class shell {
private:
	int *list;
	int size;
	int tail;
public:
	shell();
	shell(int);
	~shell();
	void insert(int);
	void sort();
	void insertSort(int, int);
	void output();
};
shell::shell() :size(10), tail(0) { this->list = new int[size]; }
shell::shell(int size) : size(size), tail(0) { this->list = new int[size]; }
shell::~shell() {}
void shell::insert(int value) { this->list[tail++] = value; }
void shell::sort() {
	int d = this->size / 2;
	while (d != 0) {
		for (int i = 0; i < d; i++) {
			this->insertSort(i, d);
		}
		d /= 2;
		this->output();
	}
}
void shell::insertSort(int start, int d) {
	for (int i = start; i < this->size; i += d) {
		int j;
		bool check = false;
		for (j = start; j < i; j += d) {
			if (this->list[i] < this->list[j]) {
				check = true;
				break;
			}
		}

		if (check) {
			int temp = list[i];
			for (int k = i; k > j; k -= d) {
				this->list[k] = this->list[k - d];
			}
			this->list[j] = temp;
		}
	}
}
void shell::output() {
	for (int i = 0; i < this->tail-1; i++) {
		cout << this->list[i] << " ";
	}
	cout <<this->list[tail-1]<< endl;
}
int main(void) {
	int n, m;
	cin >> n;
	shell test(n);
	for (int i = 0; i < n; i++) {
		cin >> m;
		test.insert(m);
	}
	test.sort();
	system("pause");
	return 0;
}
/*
希尔排序
Total number of submissions : 1023 timespassing number : 10 timesPassing rate : 0.98%

Memory limit : 20971520(BYTE)Time limit : 1000(MS)Input limit : 1000(ROWS)Output limit : 64(ROWS)

Problem description
根据输入，输出希尔排序的每趟排序结果。排序间隔从n / 2取整开始，每趟是上次间隔的1 / 2取整。n为排序数字的个数。

输入格式：输入数字为整数，先输入排序数字个数，然后输入需要排序的数字序列。

输出：每趟排序结果。

要求： 程序需要实现排序，其他可以使用stl包。



Annex

Sample of Input and Output
样例1
Input :
12
4667
5645
5
91
63
923
61
46
414
99
4
8
Output:
61 46 5 91 4 8 4667 5645 414 99 63 923
61 4 5 91 46 8 99 63 414 4667 5645 923
4 5 8 46 61 63 91 99 414 923 4667 5645
*/