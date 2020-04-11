#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define MAXN 1005
int anarr[MAXN], tryarr[MAXN];
int anvis[MAXN], tryvis[MAXN];

int main() {
	int i,j,k=0,n,a,b,c;
	while(scanf("%d", &n) == 1 && n != 0) {
		printf("Game %d:\n", ++k);
		for(i=0; i<n; ++i)
			scanf("%d", anarr+i);
		while(1) {
			memset(anvis, 0, sizeof(anvis));
			memset(tryvis, 0, sizeof(tryvis));
			c = 0;
			a = 0;
			b = 0;
			for(i=0; i<n; ++i) {
				scanf("%d", tryarr+i);
				if(tryarr[i] == 0)
					c++;
				if(tryarr[i] == anarr[i]) {
					a++;
					anvis[i] = 1;
					tryvis[i] = 1;
				}
			}
			if(c == n)
				break;
			for(i=0; i<n; ++i) {
				if(tryvis[i] == 1)
					continue;
				for(j=0; j<n; ++j) {
					if(anvis[j] == 1)
						continue;
					if(anarr[j] == tryarr[i]) {
						++b;
						anvis[j] = 1;
						tryvis[i] = 1;
						break;
					}
				}
			}
			printf("    (%d,%d)\n", a, b);
		}
	}

	return 0;
}
