#define MAXSIZE 200

#include<iostream>
#include<vector>

using namespace std;

class BigInt {
public:
	int number[MAXSIZE] = { 0 };
	int length = 0;
	BigInt() {
		length = 1;
	}
	BigInt(unsigned long long int num) {
		int i = 0;
		number[0] = num % 10;
		while (num) {
			number[i++] = num % 10;
			num /= 10;
			length++;
		}
	}
	BigInt(BigInt &a) {
		a.checklength();
		a.checkhead();
		this->length = a.length;
		for (int i = 0; i < length; i++) {
			number[i] = a.number[i];
		}
		//this->checklength();
	}
	/*
	BigInt(BigInt *a) {
		(*a).checklength();
		(*a).checkhead();
		this->length = (*a).length;
		for (int i = 0; i < length; i++) {
			number[i] = (*a).number[i];
		}
		//this->checklength();
	}
	*/
	~BigInt() {

	}
	void checklength() {
		for (int i = MAXSIZE-1; i > 0; i--) {
			if (number[i] != 0) {
				length = i + 1;
				break;
			}
		}
	}
	void checkhead() {
		while (this->number[length - 1] / 10) {
			//cout << "Length-1:" << number[length - 1] << " Length:" << length << endl;
			this->number[length] += this->number[length - 1] / 10;
			this->number[length - 1] = this->number[length - 1] % 10;
			length++;
		}
	}
	bool ascend(BigInt &a, int pos) {
		if (a.number[pos] > 9) {
			a.number[pos + 1] += a.number[pos] / 10;
			a.number[pos] %= 10;
		}
		return true;
	}
	bool ascend(int pos) {
		if (this->number[pos] > 9) {
			this->number[pos + 1] += this->number[pos] / 10;
			this->number[pos] = this->number[pos] % 10;
		}
		return true;
	}
	bool decend(BigInt &a, int pos) {

		return true;
	}
	BigInt *operator+(const BigInt &a) {
		BigInt* ans;
		ans = new BigInt;
		int anslength = (this->length > a.length) ? this->length : a.length;
		for (int i = 0; i <= anslength; i++) {
			(*ans).number[i] = this->number[i] + a.number[i];
			ascend(*ans, i);
		}
		(*ans).checklength();
		(*ans).checkhead();
		return ans;
	}
	BigInt *operator*(const BigInt &a) {
		//BigInt ansdb(0);
		BigInt* ansdb;
		ansdb = new BigInt;
		for (int i = 0; i < a.length; i++) {
			for (int j = 0; j < this->length; j++) {
				(*ansdb).number[i + j] += this->number[j] * a.number[i];
			}
		}
		(*ansdb).checklength();
		for (int i = 0; i < (*ansdb).length; i++) {
			ascend(*ansdb, i);
		}
		(*ansdb).checklength();
		(*ansdb).checkhead();
		return ansdb;
	}
	BigInt *operator*(int a) {
		BigInt* ans;
		ans = new BigInt;
		for (int j = 0; j < this->length; j++) {
			(*ans).number[j] += this->number[j] * a;
		}
		(*ans).checklength();
		for (int i = 0; i < (*ans).length; i++) {
			ascend(*ans, i);
		}
		(*ans).checklength();
		(*ans).checkhead();
		return ans;
	}
	BigInt &operator=(BigInt a) {
		a.checklength();
		a.checkhead();
		this->length = a.length;
		for (int i = 0; i < length; i++) {
			number[i] = a.number[i];
		}
		//this->checklength();
		return *this;
	}
	BigInt &operator=(BigInt *a) {
		(*a).checklength();
		(*a).checkhead();
		this->length = (*a).length;
		for (int i = 0; i < length; i++) {
			number[i] = (*a).number[i];
		}
		//this->checklength();
		return *this;
	}
	BigInt &operator=(BigInt &a) {
		a.checklength();
		a.checkhead();
		this->length = a.length;
		for (int i = 0; i < length; i++) {
			number[i] = a.number[i];
		}
		//this->checklength();
		return *this;
	}
	BigInt &operator+=(const BigInt &a) {
		for (int i = 0; i < a.length; i++) {
			this->number[i] += a.number[i];
			this->ascend(i);
		}
		this->checkhead();
		this->checklength();
		return *this;
	}
	BigInt &operator+=(const BigInt* a) {
		for (int i = 0; i < (*a).length; i++) {
			this->number[i] += (*a).number[i];
			this->ascend(i);
		}
		this->checkhead();
		this->checklength();
		return *this;
	}
	BigInt &operator*=(int a) {
		for (int j = 0; j < this->length; j++) {
			this->number[j] = this->number[j] * a;
		}
		this->checklength();
		for (int i = 0; i < this->length; i++) {
			ascend(*this, i);
		}
		this->checklength();
		this->checkhead();
		return *this;
	}
};
ostream & operator<<(ostream &out, BigInt &a) {
	a.checklength();
	a.checkhead();
	for (int i = a.length - 1; i >= 0; i--) {
		//cout << a.number[i] << " ";
		cout << a.number[i];
	}
	return out;
}

void count(const int &n, const int &a) {
	BigInt answer;
	BigInt cache(a);
	for (int i = 0; i < n; i++) {
		answer += cache * i;
		cache *= a;
	}
	cout << answer << endl;
}
//BigInt ans(0);
//BigInt answer(0);

void deal(int a, int n) {
	BigInt answer;
	BigInt cache(1);
	//cout << ans << endl;
	for (int i = 0; i < n; i++) {
		BigInt ans;
		cache *= a;
		//cout <<"ans is:"<< ans << endl;
		(ans) = cache * (i+1);
		answer += (ans);
		//answer += cache * i;
		//cout << "THe list i:" << i << endl;
		//cout << "i*A^i="<<ans << endl;
		//cout << "A^i="<<cache << endl;
		//cout << "ans="<<answer << endl;
	}
	cout << answer << endl;

}




int main(void) {
	
	int input[2000];
	int seqNum = 0, couNum = 0;

	while (cin >> input[seqNum] >> input[seqNum + 1]) {
		seqNum += 2;
	}
	while (seqNum > couNum) {
		//cout << couNum / 2 + 1 << " is :" << input[couNum] << " and " << input[couNum + 1] << endl;
		deal(input[couNum+1], input[couNum]);
		couNum += 2;
	}
	//this line*/
	/*
	BigInt a(123);
	BigInt b(12);
	BigInt c;
	BigInt d;
	BigInt e;
	cout << c << d << e<<endl;
	d = a + 12;
	c = a + b;
	e = (a * b);
	cout << e << "is e" << endl;
	e = e * 3;
	cout << e << "is e*3" << endl;
	cout << c << " a n d " << d << endl;
	deal(3, 3);
	deal(4, 4);
	*/
	system("pause");
	return 0;
}