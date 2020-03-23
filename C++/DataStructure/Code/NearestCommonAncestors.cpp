#include<iostream>
using namespace std;
int main(void) {
	int *ansSheet;
	int n, m;
	cin >> n;
	ansSheet = new int[n] {0};
	int *parentList = NULL;
	int *temp1 = NULL;
	int *temp2 = NULL;
	for (int i = 0; i < n; i++) {
		cin >> m;
		parentList = new int[m+1] {0};
		int pos, cache, rootpos;
		for (int j = 1; j < m; j++) {
			cin >> pos >> cache;
			parentList[cache] = pos;
		}
		for (int j = 1; j < m; j++) {
			if (parentList[j]==0) {
				rootpos = j;
				break;
			}
		}
		cin >> pos >> cache;
		temp1 = new int[m] {0};
		temp2 = new int[m] {0};
		int k = 0, z = 0;
		while (pos != 0) {
			temp1[k++] = pos;
			pos = parentList[pos];
		}
		while (cache != 0) {
			temp2[z++] = cache;
			cache = parentList[cache];
		}
		m = (k > z) ? z : k;
		z -= m;
		k -= m;
		for (int j = 0; j < m; j++) {
				if (temp1[j + k] == temp2[j + z]) {
					ansSheet[i] = temp1[j + k];
					break;
				}
		}
		if(parentList!=NULL){
            delete[]parentList;
		}
		if(temp1=NULL){
            delete[]temp1;
		}
		if(temp2!=NULL){
            delete[]temp2;
		}
	}
	for (int i = 0; i < n; i++) {
		cout << ansSheet[i] << endl;
	}
	delete[]ansSheet;
	return 0;
}
/*
2
16
1 14
8 5
10 16
5 9
4 6
8 4
4 10
1 13
6 15
10 11
6 7
10 2
16 3
8 1
16 12
16 7
5
2 3
3 4
3 1
1 5
3 5
*/
