#include<stdio.h>
 
bool judgeOne(int i) {
	int arr[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	for(int j = 0; j < 5; ++j) {
		arr[i % 10]++;
		i = i / 10;
	}
	for(int j = 0; j < 10; ++j)
		if(arr[j] > 1) return false;
	return true;
}
 
bool judgeTwo(int i, int j) {
	int arr[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	for(int k = 0; k < 5; ++k) {
		arr[i % 10]++;
		i = i / 10;
	}
	for(int k = 0; k < 5; ++k) {
		arr[j % 10]++;
		j = j / 10;
	}
	for(j = 0; j < 10; ++j)
		if(arr[j] > 1) return false;
	return true;
}
 
int main() {
	int n, i, j, k;
	bool flag, flagS = false;
	while(scanf("%d", &n) == 1 && n) {
		if(flagS) putchar('\n');
		flagS = true;
		k = 100000 / n;
		flag = false;
		for(i = 1234; i <= k; ++i) {
			if(!judgeOne(i)) continue;
			j = i * n;
			if(!judgeTwo(i, j)) continue;
			flag = true;
			printf("%05d / %05d = %d\n", j, i, n);
		}
		if(flag == false)
			printf("There are no solutions for %d.\n", n);
	}
	return 0;
}
