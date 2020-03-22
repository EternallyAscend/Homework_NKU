#include<stdlib.h>
#include<stdio.h>
int main(void) {
	int n;
	scanf("%d", &n);
	int *list = new int[n];
	for (int i = 0; i < n; i++) {
		scanf("%d", &list[i]);
	}
	int a = list[0];
	int b = list[0];
	int n1 = 0;
	int n2 = 0;
	for (int i = 0; i < n; i++) {
		if (list[i] == a) { 
			n1++;
			continue;
		}
		if (list[i] == b) {
			n2++;
			continue;
		}
		if(n1==0){
			a = list[i];
			n1++;
			continue;
		}
		if(n2==0){
			b = list[i];
			n2++;
			continue;
		}
		n1--;
		n2--;
	}
	n1 = n2 = 0;
	for (int i = 0; i < n; i++) {
		if (list[i] == a) { n1++; }
		if (list[i] == b) { n2++; }
	}
	int ans0 = 0;
	int ans1 = 0;
	if (n1 > n / 3) { ans0 = a; }
	if (n2 > n / 3) { ans1 = b; }
	if (ans0 != 0 && ans1 != 0) {
		int min = ans0 > ans1 ? ans1 : ans0;
		int max = ans0 > ans1 ? ans0 : ans1;
		printf("%d\n%d\n", min, max);
	}
	else {
		if (ans0 != 0) { printf("%d\n", ans0); }
		if (ans1 != 0) { printf("%d\n", ans1); }
	}
	return 0;
}
