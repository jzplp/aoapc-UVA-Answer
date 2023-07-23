#include<stdio.h>
 
int arr[20];
long long left[20];
 
int main() {
	int casei = 0, n, i, j, k;
	long long maxi, mi;
	while(scanf("%d", &n) == 1) {
		++casei;
		for(i = 0; i < n; ++i) {
			scanf("%d", &arr[i]);
		}
		maxi = 0;
		for(i = 0; i < n; ++i) {
			for(j = 0; j <= i; ++j) {
				mi = 1;
				for(k = j; k <= i; ++k) {
					mi *= arr[k];
				}
				if(maxi < mi) maxi = mi;
			}
		}
		printf("Case #%d: The maximum product is %lld.\n\n", casei, maxi);
	}
	return 0;
}
