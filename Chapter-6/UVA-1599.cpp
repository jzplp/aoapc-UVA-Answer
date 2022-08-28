#include<stdio.h>
#include<string.h>
#include<queue>
#include<vector>
#include<algorithm>

#define MAXN 100002
using namespace std;

struct Edge {
	int b, c;
};

vector<Edge> ve[MAXN];
int flagEnd[MAXN];
int flagFront[MAXN];
int pathFront[MAXN];
int path[MAXN];
int n;

void clear() {
	memset(flagEnd, 0, sizeof(flagEnd));
	memset(flagFront, 0, sizeof(flagFront));
	memset(pathFront, 0, sizeof(pathFront));
	memset(path, 0, sizeof(path));
	fill(ve, ve + MAXN, vector<Edge>());
} 

void bfsEnd() {
	int i, j;
	queue<int> qu;
	qu.push(n);
	flagEnd[n] = 1;
	while(!qu.empty()) {
		i = qu.front();
		qu.pop();
		for(j = 0; j < ve[i].size(); ++j) {
			if(!flagEnd[ve[i][j].b]) {
				flagEnd[ve[i][j].b] = flagEnd[i] + 1;
				qu.push(ve[i][j].b);
			}
		}
	}
}

void bfsBeg() {
	int i, j, k, f;
	flagFront[1] = 0;
	pathFront[1] = 0;
	queue<int> qu;
	qu.push(1);
	while(!qu.empty()) {
		i = qu.front();
		qu.pop(); 
		f = 1000000001;
		for(j = 0; j < ve[i].size(); ++j) {
			k = ve[i][j].b;
			if(flagEnd[k] != flagEnd[i] - 1) continue;
			if(ve[i][j].c >= f) continue;
			f = ve[i][j].c;
			if(flagFront[k] && pathFront[k] < f) {
				f = pathFront[k];
			}
		} 
		for(j = 0; j < ve[i].size(); ++j) {
			k = ve[i][j].b;
			if(ve[i][j].c != f || flagEnd[k] != flagEnd[i] - 1) continue;
			if(flagFront[k] && pathFront[k] > f || !flagFront[k]) {
				qu.push(k);
				flagFront[k] = i;
				pathFront[k] = f;
			}
		}
	}
}

int getPath() {
	int i = n, j = 0;
	while(flagFront[i]) {
		path[j] = pathFront[i];
		i = flagFront[i];
		++j; 
	}
	return j;
} 

void input(int m) {
	int a, b, c;
	for(int i = 0; i < m; ++i) {
		scanf("%d %d %d", &a, &b, &c);
		if(a == b) continue;
		ve[a].push_back({b, c});
		ve[b].push_back({a, c});
	}
}

int main() {
	int m, i, j, k;
	int a, b, c;
	while(scanf("%d %d", &n, &m) == 2) {
		clear();
		input(m);
		bfsEnd();
		bfsBeg();
		j = getPath();
		printf("%d\n", j);
		for(i = j - 1; i >= 0; --i) {
			if(i != j - 1) {
				putchar(' ');
			}
			printf("%d", path[i]);
		}
		putchar('\n');
	}
	return 0;
}

