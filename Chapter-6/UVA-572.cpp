#include<stdio.h>
#include<string.h>

char str[105][105];
int flg[105][105];
int m, n, cnt;

void dfs(int a, int b) {
	int i, j;
	if(a < 0 || a >= m || b < 0 || b >= n) {
		return;
	} 
	if(str[a][b] != '@' || flg[a][b]) {
		return;
	}
	flg[a][b] = 1;
	for(i = -1; i < 2; ++i) {
		for(j = -1; j < 2; ++j) {
			dfs(a + i, b + j);
		}
	}
}

int main() {
	int i, j;
	while(scanf("%d%d", &m, &n) && m) {
		for(i = 0; i < m; ++i) {
			scanf("%s", str[i]);
		}
		memset(flg, 0, sizeof(flg));
		cnt = 0;
		for(i = 0; i < m; ++i) {
			for(j = 0; j < n; ++j) {
				if(str[i][j] == '@' && !flg[i][j]) {
					++cnt;
					dfs(i, j);
				}
			}
		}
		printf("%d\n", cnt);
	}
	return 0;
} 
