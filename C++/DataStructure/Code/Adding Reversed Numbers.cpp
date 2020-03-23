#include<iostream>
#include<vector>
using namespace std;

void deal(const int &a,const int &b) {
	int lo = (a > b) ? a : b;
	int sh = (a < b) ? a : b;
	
	int listlo[100] = { 0 };
	int listsh[100] = { 0 };
	int i = 1, j = 1;
	int start,end;
	bool staflag=false, endflag=false;
	for (;lo!=0; i++) {
		listlo[i] = lo % 10;
		lo /= 10;
		
	}

	start = i-1;
	for (; sh!=0; j++) {
		listsh[j] = sh % 10;
		sh /= 10;
	}
	
	for (; j > 0; i--,j--) {
		listlo[i] += listsh[j];
	}
	for (i = start; i > 0; i--) {
		if (listlo[i] > 9) {
			listlo[i - 1] += listlo[i] / 10;
			listlo[i] %= 10;
		}
	}
	for (i = start; i >= 0; i--) {
		if (listlo[i] != 0 && !staflag) {
			
			staflag = true;
			
			start = i;
			
		}
	}
	for (i = 0; i <= start; i++) {
		
		if (listlo[i] != 0 && !endflag) {
			endflag = true;
			end = i;
			
		}
	}
	for (i = start; i >= end; i--) {
		cout << listlo[i];
	}
	cout << endl;
}


int main(void) {
	int num;
	cin >> num;
	
	vector<int> list;
	
	
	for (int i = 0; i < num; i++){
		int a, b;
		cin >> a >> b;
		list.push_back(a);
		list.push_back(b);
	}
	for (int i = 0; i < num; i++) {
		deal(list[2 * i], list[2 * i + 1]);
	}
	system("pause");
	return 0;
}