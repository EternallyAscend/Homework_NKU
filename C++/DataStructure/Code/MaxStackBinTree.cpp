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
��һϵ�и��������������һ����ʼΪ�յ�����H[]����������������±�i����ӡ��H[i]��������·����

�����ʽ:
ÿ����Ե�1�а���2��������N��M(��1000)���ֱ��ǲ���Ԫ�صĸ������Լ���Ҫ��ӡ��·����������һ�и�������[-1000, 1000]�ڵ�N��Ҫ������һ����ʼΪ�յ����ѵ����������һ�и���M���±꣨�����±�Ϊ1����

�����ʽ:
�������и�����ÿ���±�i����һ���������H[i]��������·���ϵ����нڵ㡣���ּ���1���ո�ָ���

Ҫ��
ÿ����һ��ֵ����Ҫ��֤��ǰ��HΪ���ѡ�


Annex

Sample of Input and Output
����1
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