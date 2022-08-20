#include<stdio.h>
#include<string.h>
#include<math.h>

char str[1010];
int graph[30][30];
int find[30]; 

void clear() {
	memset(str, 0, sizeof(str));
	memset(graph, 0, sizeof(graph));
	memset(find, 0, sizeof(find));
}


void dfs(int i) {
	int j, k;
	find[i] = 1; 
	for(j = 0; j < 30; ++j) {
		if(find[j] == -1 && graph[i][j] > 0) {
			dfs(j);
		}
	}
}

bool isconn() {
	int i, j, k;
	for(i = 0; i < 30; ++i) {
		if(find[i] == -1) break;
	}
	dfs(i);
	for(i = 0; i < 30; ++i) {
		if(find[i] == -1) return false;
	}
	return true;
}

bool iseuler() {
	int add = 0, sub = 0;
	int in, out, i, j;
	for(i = 0; i < 30; ++i) {
		in = 0; out = 0;
		for(j = 0; j < 30; ++j) {
			in += graph[i][j];
			out += graph[j][i];
		}
		if(in == out) {
			continue;
		}
		if(abs(in - out) > 1) {
			return false;
		}
		if(in > out) {
			++add;
		} else {
			++sub;
		}
	}
	if(add == 0 && sub == 0) {
		return true;
	}
	if(add == 1 && sub == 1) {
		return true;
	}
	return false;
}


int main() {
	int t, n;
	int beg, end;
	scanf("%d", &t);
	while(t--) {
		clear();
		scanf("%d", &n);
		while(n--) {
			scanf("%s", str);
			beg = str[0] - 'a';
			end = str[strlen(str) - 1] - 'a';
			find[beg] = -1;
			find[end] = -1;
			graph[beg][end] += 1;
		}
		if(!isconn()) {
			printf("The door cannot be opened.\n");
			continue;
		}
		if(iseuler()) {
			printf("Ordering is possible.\n");
		} else {
			printf("The door cannot be opened.\n");
		}
	}
	return 0;
}
