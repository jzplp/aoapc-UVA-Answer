#include<stdio.h>
#include<string.h>

#define MAXN 103

bool graph[MAXN][MAXN];
bool isfind[MAXN];
int list[MAXN];
int t; 

void clear() {
	memset(graph, 0, sizeof(graph));
	memset(isfind, 0, sizeof(isfind));
	memset(list, 0, sizeof(list));
	t = 0;
}

int m, n;

void input() {
	int i, j, k;
	for(i = 0; i < m; ++i) {
		scanf("%d %d", &j, &k);
		graph[j][k] = true;
	}
}

void bfs(int i) {
	int j;
	for(j = 1; j <= n; ++j) {
		if(!isfind[j] && graph[j][i]) {
			bfs(j);
		}
	}
	isfind[i] = true;
	list[++t] = i;
}

int main() {
	int i, j, k;
	while(scanf("%d %d", &n, &m) && n > 0) {
		clear();
		input();
		for(i = 1; i <= n; ++i) {
			if(!isfind[i]) {
				bfs(i);
			}
		}
		for(i = 1; i <= n; ++i) {
			if(i != 1) {
				putchar(' ');
			}
			printf("%d", list[i]);
		}
		putchar('\n');
	}
	return 0;
}
