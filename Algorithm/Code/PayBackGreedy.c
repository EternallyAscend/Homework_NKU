#pragma warning(disable:4996)

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

int main(void) {
	int number[] = {50,20,10,5,1};
	int size = 5;
	int count[5] = { 0 };
	int n;
	scanf("%d", &n);
	int i = 0;
	while (n > 0) {
		while (n >= number[i]) {
			n -= number[i];
			count[i]++;
		}
		i++;
	}
	for (i = 0; i < size; i++) {
		if (count[i] != 0) {
			if (n) { printf("+"); }
			printf("%d*%d", number[i], count[i]);
			n = 1;
		}
	}
	system("pause");
	return 0;
}