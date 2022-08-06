#include<stdio.h>
#include<string.h>

int sum[100];

bool subTree(int p) {
	int v;
	if(scanf("%d", &v) <= 0 || v <= 0) {
		return false;
	}
	sum[p] += v;
	subTree(p-1);
	subTree(p+1);
	return true;
}

int main() {
	int i, n = 0;
	memset(sum, 0, sizeof(sum));
	while(subTree(50)) {
		printf("Case %d:\n", ++n);
		i = 0;
		while(sum[i] == 0) ++i;
		printf("%d", sum[i++]);
		for(; i < 100; ++i) {
			if(sum[i] != 0) {
				printf(" %d", sum[i]);
			}
		}
		printf("\n\n");
		memset(sum, 0, sizeof(sum));
	}
	return 0;
} 
