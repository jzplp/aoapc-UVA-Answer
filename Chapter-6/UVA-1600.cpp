#include<stdio.h>
#include<string.h>
#include<queue>

using namespace std;

int m, n, k;
int graph[22][22]; 
int dist[22][22];

struct Node {
	int x, y;
	int num, ti;
};

int step1[4] = {1, 0, -1,  0};
int step2[4] = {0, 1,  0, -1};

void bfs() {
	int i, j, x, y;
	memset(dist, 0, sizeof(dist));
	queue<Node> qu;
	Node no1, no2 = {0, 0, 0, 0};
	qu.push(no2);
	while(!qu.empty()) {
		no1 = qu.front();
		qu.pop();
		// printf("%d %d %d %d\n", no1.x, no1.y, no1.ti, no1.num);
		for(i = 0; i < 4; ++i) {
			x = no1.x + step1[i];
			y = no1.y + step2[i];
			if(x < 0 || x >= m) continue;
			if(y < 0 || y >= n) continue;
			if(x == m-1 && y == n-1) {
				dist[m-1][n-1] = no1.num + 1;
				return;
			}
			if(dist[x][y] != 0 && dist[x][y] < no1.num+1) continue;
			if(graph[x][y] && no1.ti+1 > k) continue;
			dist[x][y] = no1.num+1;
			if(graph[x][y]) {
				qu.push({x, y, no1.num+1, no1.ti+1});
			} else {
				qu.push({x, y, no1.num+1, 0});
			}
		}
	}
	return;
}

int main() {
	int t;
	int i, j; 
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d %d", &m ,&n, &k);
		for(i = 0; i < m; ++i) {
			for( j = 0; j < n; ++j) {
				scanf("%d", &graph[i][j]);
			}
		}
		if(m == 1 && n == 1) {
			printf("0\n");
			continue;
		}
		bfs();
		if(dist[m-1][n-1] == 0) {
			printf("-1\n");
		} else {
			printf("%d\n", dist[m-1][n-1]);
		}
	}
	return 0;
} 
