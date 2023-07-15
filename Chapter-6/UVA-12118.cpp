#include<stdio.h>
#include<vector>
#include<algorithm>
#include<string.h>
using namespace std;
 
vector<int> graph[1010];
int arrFind[1010];
int v, e, t;
 
int traverse(int start) {
	int i;
	int value = 0;
	arrFind[start] = 1;
	if(graph[start].size() % 2 != 0) {
		++value;
	}
	for(i = 0; i < graph[start].size(); ++i) {
		if(!arrFind[graph[start][i]])
			value += traverse(graph[start][i]);
	}
	return value;
}
 
int main() {
	int sum, n = 0, i, a, b, plusA;
	while(scanf("%d %d %d", &v, &e, &t) == 3 && v != 0) {
		++n;
		for(i = 1; i <= v; ++i) {
			graph[i].clear();
			arrFind[i] = 0;
		}
		for(i = 0; i < e; ++i) {
			scanf("%d %d", &a, &b);
			graph[a].push_back(b);
			graph[b].push_back(a);
		}
		// ШЅжи
		for(i = 1; i <= v; ++i) {
			if(graph[i].size() < 2) continue;
			sort(graph[i].begin(), graph[i].end());
			vector<int>::iterator qit = unique(graph[i].begin(),graph[i].end());
			graph[i].erase(qit, graph[i].end());
		}
		sum = 0; a = 0;
		for(i = 1; i <= v; ++i) {
			if(arrFind[i] || !graph[i].size()) continue;
			++a; 
			plusA = traverse(i) / 2;
			if(plusA < 2) continue;
			sum += plusA - 1;
		}
		if(e == 0) {
			printf("Case %d: %d\n", n, 0);
			continue;
		}
		printf("Case %d: %d\n", n, (e + sum + a - 1) * t);
	}
	return 0;
}
