#include<stdio.h>
#include<string.h>

#define MAXN 55

int graph[MAXN][MAXN];
int flag[MAXN];
int has[MAXN]; 
char str[10];

void handlestr() {
	int i, j;
	char arr[4];
	for(i = 0; i < 4; ++i) {
		if(str[2*i] == '0') {
			arr[i] = -1;
			continue;
		}
		arr[i] = (str[2*i] - 'A') * 2 + ((str[2*i+1] == '+') ? 0 : 1);
		has[arr[i]] = 1;
	}
	for(i = 0; i < 4; ++i) {
		if(arr[i] == -1) continue; 
		for(j = i+1; j < 4; ++j) {
			if(arr[j] == -1) continue; 
			graph[arr[i]][arr[j]] = 1;
			graph[arr[j]][arr[i]] = 1;
		}
	}
}

bool dfs(int i) {
	i = (i % 2 == 0) ? i + 1 : i - 1;
	if(!has[i]) {
		return false;
	}
	if(flag[i]) {
		return true;
	}
	flag[i] = true;
	int j;
	for(j = 0; j < MAXN; ++j) {
		if(graph[i][j]) {
			if(dfs(j)) {
				return true;
			}
		}
	}
	flag[i] = false;
	return false;
}

bool count() {
	int i, j;
	for(i = 0; i < MAXN; ++i) {
		if(has[i]) {
			flag[i] = true;
			for(j = 0; j < MAXN; ++j) {
				memset(flag, 0, sizeof(flag));
				flag[i] = true;
				if(graph[i][j]) {
					if(dfs(j)) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

int main() {
	int n, i;
	while(scanf("%d", &n) > 0) {
		memset(graph, 0, sizeof(graph));
		memset(has, 0, sizeof(has));
		memset(flag, 0, sizeof(flag));
		for(i = 0; i < n; ++i) {
			scanf("%s", str);
			handlestr();
		}
		if(!count()) {
			puts("bounded");
		} else {
			puts("unbounded");
		}
	}
	return 0;
}
