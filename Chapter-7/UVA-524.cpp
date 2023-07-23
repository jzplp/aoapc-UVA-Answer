#include<stdio.h>
#include<string.h>
 
int PrimeArr[33] = {0, 0,1,1,0,1, 0,1,0,0,0, 1,0,1,0,0, 0,1,0,1,0, 0,0,1,0,0, 0,0,0,1,0, 1,0};
int n;
int arr[20];
int flagArr[20];
 
void dfs(int cus) {
	int i;
	if(cus == n) {
		if(PrimeArr[arr[n-1] + arr[0]]) {
			for(i = 0; i < n; ++i) {
				if(i != 0) putchar(' ');
				printf("%d", arr[i]);
			}
			putchar('\n');
		}
		return;
	}
	for(i = 1; i <= n; ++i) {
		if(flagArr[i] || !PrimeArr[arr[cus - 1] + i]) {
			continue;
		}
		flagArr[i] = 1;
		arr[cus] = i;
		dfs(cus + 1);
		flagArr[i] = 0;
	}
}
 
int main() {
	int t = 0;
	while(scanf("%d", &n) == 1) {
		if(t) putchar('\n');
		++t;
		memset(flagArr, 0, sizeof(flagArr));
		arr[0] = 1;
		flagArr[1] = 1;
		printf("Case %d:\n", t);
		dfs(1);
	}
	return 0;
}
