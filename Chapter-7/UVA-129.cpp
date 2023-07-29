#include<stdio.h>

int n, l, cur;
int arr[100];
bool flag; 

void print(int i) {
	for(int j = 1; j <= i; ++j) {
		printf("%c", 'A' + arr[j]);
		if(j%4 == 0 && j != i && j != 64) putchar(' ');
		if(j == 64 && j != i) putchar('\n');
	}
	printf("\n%d\n", i);
}

bool judge(int i) {
	int j, k;
	for(j = 1; j <= i/2; ++j) {
		for(k = 0; k < j; ++k) {
			if(arr[i - k] != arr[i - k - j]) break;
		}
		if(k == j) return false;
	}
	return true;
}

void dfs(int i) {
	if(i > 0 && !judge(i)) {
		return;
	}
	++cur;
	if(cur == n) {
		print(i);
		flag = true;
		return;
	}
	for(int j = 0; j < l; ++j) {
		arr[i+1] = j;
		dfs(i + 1); 
		if(flag) return;
	}
}

int main() {
	while(scanf("%d %d", &n, &l) == 2 && n) {
		cur = -1; flag = false;
		dfs(0);
	}
	return 0;
} 
