#include<iostream>
#include<string>
#include<cmath>
using namespace std;
class minStack {
private:
	int *list;
	int size;
	int tail;
	//bool notEmpty;
public:
	minStack();
	minStack(int size);
	~minStack();
	bool smaller(int value, int pos);
	void insert(int value);
	void output();
	int getRoot();
	int position(int value);
	bool checkParentAndChild(int x, int y);
	bool checkSiblings(int x, int y);
};
minStack::minStack() {

}
minStack::minStack(int size) {
	list = new int[size];
	this->size = size;
	tail = 0;
	//notEmpty = false;
}
minStack::~minStack() {

}
bool minStack::smaller(int value, int pos) {
	if ((pos - 1) >= 0) {
		if (value < list[(pos - 1) / 2]) {
			list[pos] = list[(pos - 1) / 2];
			list[(pos - 1) / 2] = value;
			smaller(value, (pos - 1) / 2);
			return true;
		}
	}
	return false;
}
void minStack::insert(int value) {
	list[tail++] = value;
	smaller(value, tail - 1);
}
void minStack::output() {
	for (int i = 0; i < tail; i++) {
		cout << list[i] << endl;
	}
}
int minStack::position(int value) {
	for (int i = 0; i < tail; i++) {
		if (list[i] == value) {
			return i;
		}
	}
	return -1;
}
int minStack::getRoot() {
	return list[0];
}
bool minStack::checkSiblings(int x, int y) {
	int xp = position(x);
	int yp = position(y);
	if ((xp - 1) / 2 >= 0) {
		xp = list[(xp - 1) / 2];
	}
	if ((yp - 1) / 2 >= 0) {
		yp = list[(yp - 1) / 2];
	}
	if (xp == yp) {
		return true;
	}
	else return false;
}
bool minStack::checkParentAndChild(int parent, int child) {
	int pos = position(child);
	while ((int)(pos - 1) / 2 >= 0) {
		if (list[pos] == parent) {
			return true;
		}
		pos = (int)(pos - 1) / 2;
		if(pos==0){
            if(list[pos]==parent){
                return true;
            }
            else return false;
		}
	}
	return false;
}
int main(void) {
	int n, m, temp;
	cin >> n >> m;
	minStack t(n);
	bool *ansList;
	ansList = new bool[m];
	for (int i = 0; i < n; i++) {
		cin >> temp;
		t.insert(temp);
	}
	string cache;
	getline(cin, cache);
	for (int i = 0; i < m; i++) {
		getline(cin, cache);
		if (cache.find("root") < cache.length()) {
			string temp1;
			bool zf=false;
			for (int j = 0; j < cache.find("i")-1;j++) {
                if(cache[j]!='-'){
                    temp1.push_back(cache[j]);
                }
                else{zf=true;}
			}
			int ans = 0;
			for (int j = 0; j < temp1.length(); j++) {
				ans += (temp1[temp1.length() - j - 1] - 48) * pow(10,j);
			}
			if(zf){
                ans=0-ans;
			}
			if (ans == t.getRoot()) {
				ansList[i] = true;
			}
			else {
				ansList[i] = false;
			}
		}
		if (cache.find("siblings") < cache.length()) {
			string temp1, temp2;
			bool zf1,zf2;
			zf1=zf2=false;
			int value1, value2;
			for (int j = 0; j < cache.find("and") - 1; j++) {
                if(cache[j]!='-'){
                    temp1.push_back(cache[j]);
                }
                else zf1=true;
			}
			for (int j = cache.find("and") + 4; j < cache.find("are") - 1; j++) {
                if(cache[j]!='-'){
                    temp2.push_back(cache[j]);
				}
				else zf2=true;
			}
			value1 = value2 = 0;
			for (int j = 0; j < temp1.length(); j++) {
				value1 += (temp1[temp1.length() - j - 1] - 48) * pow(10, j);
			}
			for (int j = 0; j < temp2.length(); j++) {
				value2 += (temp2[temp2.length() - j - 1] - 48)*pow(10, j);
			}
			if(zf1) value1=0-value1;
			if(zf2) value2=0-value2;
			ansList[i] = t.checkSiblings(value1, value2);
		}
		if (cache.find("parent") < cache.length()) {
			string temp1, temp2;
			bool zf1,zf2;
			zf1=zf2=false;
			int value1, value2;
			for (int j = 0; j < cache.find("is") - 1; j++) {
                if(cache[j]!='-'){
				    temp1.push_back(cache[j]);
				}
                else zf1=true;
			}
			for (int j = cache.find("of") + 3; j < cache.length(); j++) {
                if(cache[j]!='-'){
				    temp2.push_back(cache[j]);
                }
                else zf2=true;
			}
			value1 = value2 = 0;
			for (int j = 0; j < temp1.length(); j++) {
				value1 += (temp1[temp1.length() - j - 1] - 48) * pow(10, j);
			}
			for (int j = 0; j < temp2.length(); j++) {
				value2 += (temp2[temp2.length() - j - 1] - 48)*pow(10, j);
			}
			if(zf1) value1=0-value1;
			if(zf2) value2=0-value2;
			ansList[i] = t.checkParentAndChild(value1, value2);
		}
		if (cache.find("child") < cache.length()) {
			string temp1, temp2;
			bool zf1,zf2;
			zf1=zf2=false;
			int value1, value2;
			for (int j = 0; j < cache.find("is") - 1; j++) {
                if(cache[j]!='-'){
				    temp1.push_back(cache[j]);
				}
                else zf1=true;
			}
			for (int j = cache.find("of") + 3; j < cache.length(); j++) {
                if(cache[j]!='-'){
				    temp2.push_back(cache[j]);
                }
                else zf2=true;
			}
			value1 = value2 = 0;
			for (int j = 0; j < temp1.length(); j++) {
				value1 += (temp1[temp1.length() - j - 1] - 48) * pow(10, j);
			}
			for (int j = 0; j < temp2.length(); j++) {
				value2 += (temp2[temp2.length() - j - 1] - 48)*pow(10, j);
			}
			if(zf1) value1=0-value1;
			if(zf2) value2=0-value2;
			ansList[i] = t.checkParentAndChild(value2, value1);
		}
	}
	for (int i = 0; i < m; i++) {
		if (ansList[i]) {
			cout << "T" << endl;
		}
		else {
			cout << "F" << endl;
		}
	}
	return 0;
}

/*
Input:
5 4
46 23 26 24 10
24 is the root
26 and 23 are siblings
46 is the parent of 23
23 is a child of 10
Output:
F
T
F
T
5 4
-46 -23 -26 -24 -10
-46 is the root
-26 and -24 are siblings
-46 is the parent of -23
-23 is a child of -46
*/
