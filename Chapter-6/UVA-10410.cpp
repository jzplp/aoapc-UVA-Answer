#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std; 

int n;
int bfs[1010];
int bfsPos[1010];
int dfs[1010];
int dfsPos[1010];

int near[1010]; 
vector<int> arr[1010];


void constructTree() {
	if(n < 2) return;
	int i, j, k;
	for(i = n-1; i > 1; --i) {
		for(j = i-1; j >= 0; --j) {
			if(bfsPos[dfs[i]] == bfsPos[dfs[j]] + 1 && dfs[i] > dfs[j]) {
				near[dfs[j]] = dfs[i];
				break;
			}
			if(bfsPos[dfs[i]] >= bfsPos[dfs[j]] + 1) {
				arr[dfs[j]].push_back(dfs[i]);
				break;
			}
		}
	}
	arr[dfs[0]].push_back(dfs[1]);
	for(i = 0; i < n; ++i) {
		for(j = 0; j < arr[i].size(); ++j) {
			if(near[arr[i][j]]) arr[i].push_back(near[arr[i][j]]);
		}
	}
}

int main() {
	int i, j;
	while(scanf("%d", &n) == 1 && n > 0) {
		for(i = 0; i < n; ++i) scanf("%d", &bfs[i]);
		for(i = 0; i < n; ++i) scanf("%d", &dfs[i]);
		for(i = 0; i < n; ++i) {
			bfsPos[bfs[i]] = i;
			dfsPos[dfs[i]] = i;
		}
		for(i = 1; i <= n; ++i) {
			arr[i] = vector<int>();
			near[i] = 0;
		}
		constructTree();
		for(i = 1; i <= n; ++i) {
			sort(arr[i].begin(), arr[i].end());
			printf("%d:", i);
			for(j = 0; j < arr[i].size(); ++j) printf(" %d", arr[i][j]);
			putchar('\n');
		}
	}
	return 0;
}
