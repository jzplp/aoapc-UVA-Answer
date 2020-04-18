#include<cstdio>

#define MAXN 12
char arr[MAXN][MAXN];
int num[MAXN][MAXN];

int main() {
	int r, c, t, i,j,k,n;
	n = 0;
	while(scanf("%d %d", &r, &c) == 2) {
		if(n != 0)
			puts("");
		for(i=1; i<=r; ++i)
			for(j=1; j<=c; ++j)
				scanf(" %c", &arr[i][j]);
		k = 0;
		for(i=1; i<=r; ++i)
			for(j=1; j<=c; ++j) {
				if(arr[i][j] == '*')
					continue;
				if(i == 1 || j == 1)
					num[i][j] = ++k;
				else if(arr[i][j-1] == '*' || arr[i-1][j] == '*')
					num[i][j] = ++k;
			}
		printf("puzzle #%d:\nAcross\n", ++n);
		for(i=1; i<=r; ++i) {
			j = 1;
			while(j <= c) {
				if(arr[i][j] == '*') {
					++j;
					continue;
				}
				printf("%3d.",num[i][j]);
				while(j <= c && arr[i][j] != '*')
					putchar(arr[i][j++]);
				puts("");
			}
		}
		puts("Down");
		for(i=1; i<=r; ++i)
			for(j=1; j<=c; ++j) {
				if(arr[i][j] == '*')
					continue;
				if(i == 1) {
					printf("%3d.",num[i][j]);
					for(k=i; k<=r && arr[k][j] != '*'; ++k)
						putchar(arr[k][j]);
					puts("");
					continue;
				}
				if(arr[i-1][j] == '*') {
					printf("%3d.",num[i][j]);
					for(k=i; k<=r && arr[k][j] != '*'; ++k)
						putchar(arr[k][j]);
					puts("");
					continue;
				}
			}
	}
	return 0;
}
