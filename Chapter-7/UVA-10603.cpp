#include<stdio.h>
#include<queue>
using namespace std;

struct Node {
	int v[3];
	int dist;
	bool operator < (const Node &r) const {
		return dist > r.dist; 
	}
}; 

int vis[202][202];
int dist[202]; 
int volume[3], d;

bool judge(Node * no) {
	for(int i = 0; i < 3; ++i) {
		if(no->v[i] == d) return true;
	}
	return false;
}

void handleOne(Node * no) {
	for(int i = 0; i < 3; ++i) {
		if(dist[no->v[i]] == -1 || dist[no->v[i]] > no->dist) dist[no->v[i]] = no->dist; 
	}
}

bool getNextNode(Node * no, int i, int j, Node * no2) {
	int k;
	if(no->v[i] == 0 || i == j || no->v[j] == volume[j])
		return false;
	int jLen = volume[j] - no->v[j]; 
	int minLen = jLen > no->v[i] ? no->v[i] : jLen;
	for(k = 0; k < 3; ++k) {
		no2->v[k] = no->v[k];
	}
	no2->dist = no->dist + minLen;
	no2->v[i] -= minLen;
	no2->v[j] += minLen;
	return true;
}

void compute() {
	Node no, no2;
	int i, j, k;
	priority_queue<Node> pq;
	no.v[0] = 0; no.v[1] = 0; no.v[2] = volume[2]; no.dist = 0; 
	pq.push(no);
	while(!pq.empty()) {
		no = pq.top();
		pq.pop();
		handleOne(&no);
		if(judge(&no)) return;
		for(i = 0; i < 3; ++i) {
			for(j = 0; j < 3; ++j) {
				if(!getNextNode(&no, i, j, &no2)) continue;
				if(vis[no2.v[0]][no2.v[1]]) continue;
				vis[no2.v[0]][no2.v[1]] = 1;
				pq.push(no2);
			}
		}
	}
}

void init() {
	for(int i = 0; i < 202; ++i) {
		dist[i] = -1;
		for(int j = 0; j < 202; ++j) {
			vis[i][j] = 0;
		}
	} 
}

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d %d %d", &volume[0], &volume[1], &volume[2], &d);
		init();
		compute();
		while(d >= 0) {
			if(dist[d] != -1) {
				printf("%d %d\n", dist[d], d);
				break;
			}
			--d;
		}
	}
	return 0;
} 
