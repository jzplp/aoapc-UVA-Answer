#include<stdio.h>

int main() {
	int n, i, d;
	int j, k;
	scanf("%d", &n);
	while(n--) {
		scanf("%d %d", &d, &i);
		k = 1;
		for(j = 1; j < d; ++j) {
			if(i % 2) {
				k = k * 2;
				i = (i + 1) / 2;
			} else {
				k = k * 2 + 1;
				i = i / 2;
			}
		}
		printf("%d\n", k);
	}
	return 0;
} 
