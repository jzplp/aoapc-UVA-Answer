#include<stdio.h>
#include<queue>
using namespace std;

int m; 

int findTime(queue<int> &qu, priority_queue<int> &qup) {
	int time = 0;
	int k, kt;
	while(1) { 
		k = qu.front();
		kt = qup.top();
		qu.pop();
		--m;
		if(k == kt) {
			++time;
			qup.pop();
			if(m == -1) {
				return time;
			}
		} else {
			qu.push(k);
			if(m == -1) {
				m = qu.size() - 1;
			}
		}
	}
}

int main() {
	int t, n, i, k;
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d", &n, &m);
		queue<int> qu;
		priority_queue<int> qup;
		for(i=0; i<n; ++i) {
			scanf("%d", &k);
			qu.push(k);
			qup.push(k);
		}
		printf("%d\n", findTime(qu, qup));
	}
	return 0;
}
