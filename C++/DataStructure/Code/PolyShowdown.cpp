#include<iostream>
#include<cmath>
#include<stdlib.h>
#include<vector>
using namespace std;
int main(void) {
	vector<int> list;
	int cache;
	while (cin >> cache) {
		list.push_back(cache);
	}
	int pos=0;
	while (pos<list.size()) {
		bool start = true, empty = true;
		for (int i = 0; i < 9; i++) {
			if (list[pos + i] != 0) {
				empty = false;
				if (start) {
					start = false;
					if (i == 8) {
							cout << list[pos + i];
					}
					else {
						if (8 - i > 1) {
							if (list[pos + i] == 1) {
								cout << "x^" << (8 - i);
							}
							else if (list[pos + i] == -1) {
								cout << "-x^" << (8 - i);
							}

							else {
								cout << list[pos + i] << "x^" << (8 - i);
							}
						}
						else {
							if (list[pos + i] == 1) {
								cout << "x";
							}
							else if (list[pos + i] == -1) {
								cout << "-x" ;
							}

							else {
								cout << list[pos + i] << "x" ;
							}
						}
						
					}
				}
				else {
					if (i == 8) {
						if (list[pos + i] > 0) {
							cout << " + " << list[pos + i];
						}
						else{
							cout << " - " << -list[pos + i];
						}
					}
					else {
						if (list[pos + i] > 1) {
							if (8 - i == 1) {
								cout << " + " << list[pos + i] << "x";
							}
							else {
								cout << " + " << list[pos + i] << "x^" << (8 - i);
							}
							
						}
						else if(list[pos+i]<-1){
							if (8 - i == 1) {
								cout << " - " << -list[pos + i] << "x";
							}
							else {
								cout << " - " << -list[pos + i] << "x^" << (8 - i);
							}
						}
						else if (list[pos + i] == 1) {
							if (8 - i == 1) {
								cout << " + x" ;
							}
							else {
								cout << " + x^" << (8 - i);
							}
						}
						else if (list[pos + i] == -1) {
							if (8 - i == 1) {
								cout << " - x";
							}
							else {
								cout << " - x^" << (8 - i);
							}
						}
					}
				}
			}
		}
		if (empty) {
			cout << "0";
		}
		pos += 9;
		cout << endl;
	}
	system("pause");
	return 0;
}