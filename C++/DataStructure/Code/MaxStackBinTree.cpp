#include<iostream>
using namespace std;
class MaxStack {
private:
	int *H;
	int size;
	int length;
	bool empty;
public:
	MaxStack();
	MaxStack(int length);
	~MaxStack();
	bool insert(int value);
	void print(int pos);
	bool bigger(int pos, int value);
	void read();
};
MaxStack::MaxStack() {

}
MaxStack::MaxStack(int length) {
	this->length = length;
	this->H = new int[length] {0};
	this->empty = true;
	this->size = 0;
}
MaxStack::~MaxStack() {

}
bool MaxStack::insert(int value) {
	if (this->empty) {
		this->H[0] = value;
		this->size++;
		this->empty = false;
	}
	else {
		this->H[size] = value;
		bigger(this->size, value);
		size++;
	}
	return true;
}
void MaxStack::print(int pos) {
	cout << this->H[pos];
	for (int i = (pos - 1) / 2; i > 0; i = (i - 1) / 2) {
		cout << " " << this->H[i];
	}
	if (pos > 0) {
		cout << " " << this->H[0] << endl;
	}	
}
bool MaxStack::bigger(int pos, int value) {
	if (value > this->H[(pos - 1) / 2]) {
		this->H[pos] = this->H[(pos - 1) / 2];
		this->H[(pos - 1) / 2] = value;
		if ((pos - 1) / 2 > 0) {
			this->bigger((pos - 1) / 2, value);
		}
	}
	return true;
}
void MaxStack::read() {
	for (int i = 0; i < this->size; i++) {
		cout << this->H[i] << " ";
	}
}
int main(void) {
	int n, m;
	cin >> n >> m;
	MaxStack test(n);
	int temp;
	for (int i = 0; i < n; i++) {
		cin >> temp;
		test.insert(temp);
	}
	for (int i = 0; i < m; i++) {
		cin >> temp;
		test.print(temp-1);
	}
	system("pause");
	return 0;
}
/*
Problem description
将一系列给定数字逐个插入一个初始为空的最大堆H[]。随后对任意给定的下标i，打印从H[i]到根结点的路径。

输入格式:
每组测试第1行包含2个正整数N和M(≤1000)，分别是插入元素的个数、以及需要打印的路径条数。下一行给出区间[-1000, 1000]内的N个要被插入一个初始为空的最大堆的整数。最后一行给出M个下标（根的下标为1）。

输出格式:
对输入中给出的每个下标i，在一行中输出从H[i]到根结点的路径上的所有节点。数字间以1个空格分隔。

要求：
每插入一个值，都要保证当前的H为最大堆。


Annex

Sample of Input and Output
样例1
Input:
5 4
46 23 26 24 10
5 4 3 1
Output:
10 24 46
23 24 46
26 46
46
*/