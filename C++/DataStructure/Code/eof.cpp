/*#include<iostream>
using namespace std;
int main(void) {
	int N, A, i = 0;		
	int ans[1000] = {0};
	
	while (cin>>N>>A) {
		//cin >> A;
		for (int j = 1; j <= N; j++) {
			ans[i] += j * pow(A, j);
		}
		i++;
	}
	int j = i;
	i = 0;
	while (i<j) {
		cout << ans[i] << endl;
		i++;
	}
	//system("pause");
	return 0;
}
*/
/*
	while (N = cin.get()&& N!=EOF) {
		cin >> A;
		for (int j = 1; j <= N; j++) {
			ans[i] += j * pow(A, j);
		}
		i++;
	}
	*/

#include<iostream>
#include<cmath>
using namespace std;
int main(void) {
	//int a, b;
	//cin >> a >> b;
	cout << pow(2, 64);
	//cout << pow(a, b);
	int N, A, i = 0;
	unsigned long long int ans[1000] = { 0 };
	//int ans[1000] = { 0 };
	while (cin >> N >> A) {
		for (int j = 1; j <= N; j++) {
			//ans[i] += j * pow(A, j);
			///*
			unsigned long long int cache=1;
			for (int k = 1; k <= j; k++) {
				cache *= A;
			}
			ans[i] += (cache * j);
			//*/
		}
		i++;
	}
	int j = i;
	i = 0;
	while (i < j) {
		cout << ans[i] << endl;
		i++;
	}
	system("pause");
	return 0;
}