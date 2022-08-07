#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXN 220 

char str[60];
bool fig[MAXN][MAXN];
bool figCopy[MAXN][MAXN];
bool flg[MAXN][MAXN];
bool flgCopy[MAXN][MAXN];
int w, h;


void dfs(int a, int b) {
	if(a < 0 || a > (w + 4) || b < 0 || b > MAXN) {
		return;
	}
	if(!fig[a][b] || flg[a][b]) {
		return;
	}
	figCopy[a][b] = true;
	flg[a][b] = true;
	dfs(a - 1, b);
	dfs(a + 1, b);
	dfs(a, b - 1);
	dfs(a, b + 1);
}

void dfsCopy(int a, int b) {
	if(a < 0 || a > (w + 4) || b < 0 || b > MAXN) {
		return;
	}
	if(figCopy[a][b] || flgCopy[a][b]) {
		return;
	}
	flgCopy[a][b] = true;
	dfsCopy(a - 1, b);
	dfsCopy(a + 1, b);
	dfsCopy(a, b - 1);
	dfsCopy(a, b + 1);
}


char count(int a, int b) {
	int i, j, k;
	memset(figCopy, 0, sizeof(figCopy));
	memset(flgCopy, 0, sizeof(flgCopy));
	dfs(a, b);
	k = 0;
	for(i = 0; i < (w + 4); ++i) {
		for(j = 0; j < MAXN; ++j) {
			if(!figCopy[i][j] && !flgCopy[i][j]) {
				++k;
				dfsCopy(i, j);
			}
		}
	}
	switch(k - 1) {
		case 0: return 'W';
		case 1: return 'A';
		case 2: return 'K';
		case 3: return 'J';
		case 4: return 'S';
		case 5: return 'D';
	}
}

int cmp(const void *a, const void *b) {
	return *(const char *)a > *(const char *)b;
}

int main() {
	int n = 0, i, j, k;
	while(scanf("%d%d", &w, &h) == 2 && w && h) {
		memset(fig, 0, sizeof(fig));
		memset(flg, 0, sizeof(flg));
		for(i = 1; i <= w; ++i) {
			scanf("%s", str);
			for(j = 1; j <= h; ++j) {
				if(str[j - 1] >= '0' && str[j - 1] <= '9') {
					str[j - 1] -= '0';
				} else {
					str[j - 1] = str[j - 1] - 'a' + 10;
				}
				fig[i][j*4 + 3] = str[j-1] % 2;
				str[j-1] /= 2;
				fig[i][j*4 + 2] = str[j-1] % 2;
				str[j-1] /= 2;
				fig[i][j*4 + 1] = str[j-1] % 2;
				str[j-1] /= 2;
				fig[i][j*4] = str[j-1] % 2;
			}
		}
		memset(str, 0, sizeof(str));
		k = 0; 
		for(i = 0; i < (w + 4); ++i) {
			for(j = 0; j < MAXN; ++j) {
				if(fig[i][j] && !flg[i][j]) {
					str[k++] = count(i, j);
				}
			}
		}
		qsort(str, strlen(str), sizeof(str[0]), cmp); 
		printf("Case %d: %s\n", ++n, str);
	}
	return 0;
}
