#include<stdio.h>
#include<math.h>
long long n, sp, sq;

int main() {
	unsigned long long a,b,i,j, pi;
	unsigned long long kt, k;
	while(scanf("%lld%lld%lld", &n, &sp, &sq) == 3) {
		pi = sp * (n-1);
		k = ~0;
		for(i = 0; i < 32; ++i) {
			for(j = 0; j < 32; ++j) {
				kt = ((pi + (pi << i)) >> j) + sq;
				if(sp+(sp<<i)>=(sq<<j) && kt < k && kt >= n * sq) {
					k = kt;
					a = i;
					b = j;
				}
			}
		}
		printf("%lld %lld %lld\n", k, a, b);
	}
	return 0;
} 