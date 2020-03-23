#include<iostream>
#include<stdlib.h>
using namespace std;
class Stack {
public:
	int * list;
	int length;
	Stack();
	Stack(int StackLength);
	~Stack();
	int Pop();
	void Push(int value);
	bool isNotEmpty();
};
Stack::Stack() {
	length = 0;
	list = new int[10];
	for (int i = 0; i < 10; i++) {
		list[i] = 0;
	}
}
Stack::Stack(int StackLength) {
	length = StackLength;
	list = new int[StackLength];
	for (int i = 0; i < StackLength; i++) {
		list[i] = 0;
	}
}
Stack::~Stack() {
	///delete[]list;
}
int Stack::Pop() {
	int cache = list[length-1];
	list[--length] = 0;
	return cache;
}
void Stack::Push(int value) {
	list[length++] = value;
}
bool Stack::isNotEmpty() {
	return (bool)length;
}
int cache = 0;
void Output(int n, int max, Stack stack, int ans[], int anslength) {
	if (n > max) {
		for (int k = 0; k < anslength; k++) {
			cout << ans[k];
		}
		cache++;
		for (int i = stack.length; i > 0;) {
			cout << stack.list[--i];
		}
		cout << endl;
	}
	else {
		if (stack.isNotEmpty()) {

			ans[anslength] = stack.Pop();
			Output(n, max, stack, ans, anslength + 1);
			stack.Push(ans[anslength]);
		}
		stack.Push(n);
		Output(n + 1, max, stack, ans, anslength);
	}
}
int number(int n) {
	int ansNum = 0;
	if (n == 0) {
		return 1;
	}
	if (n == 1) {
		return 1;
	}
	else {
		for (int i = 0; i < n; i++) {
			ansNum += number(i)*number(n - i - 1);
		}
	}
	return ansNum;
}
int main(void) {
	int n, num;
	cin >> n;
	int * ans;
	ans = new int[10];
	for (int i = 0; i < 10; i++) {
		ans[i] = 0;
	}
	Stack stack;
	num = number(n);
	cout << num << endl;
	if (num<=100) {
		Output(1, n, stack, ans, 0);
	}
	delete ans;
	system("pause");
	return 0;
}
