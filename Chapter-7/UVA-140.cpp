#include<stdio.h>
#include<string.h>

char line[200];
int graph[30][30];
int vlen;
int hasArr[30];
int hasLen;
 
int disArr[30];
int flagArr[30];
int minWidth;
int minArr[30];

int getNum(char c) {
	return c - 'A' + 1;
}

void handleGraph() {
	int i, j, v, vb;
	i = 0;
	while(1) {
		v = getNum(line[i]);
		if(v > vlen) vlen = v;
		++i;
		if(line[i] != ':') continue;
		if(line[i] == 0) break;
		++i;
		while(line[i] != 0 && line[i] != ';') {
			vb = getNum(line[i]);
			if(vb > vlen) vlen = vb;
			graph[v][vb] = 1;
			graph[vb][v] = 1;
			++i;
		}
		if(line[i] == 0) break;
		++i;
	}
	for(i = 1; i <= vlen; ++i) {
		for(j = 1; j <= vlen; ++j) {
			if(graph[i][j]) break;
		}
		if(j > vlen) {
			hasArr[i] = 0;
		} else {
			hasArr[i] = 1;
			++hasLen;
		}
	}
}

void getDis(int cur, int dis) {
	int i;
	for(i = 1; i <= cur - 1; ++i) {
		if(!graph[disArr[i]][disArr[cur]]) continue;
		if(minWidth <= cur - i) return;
		if(cur - i > dis) {
			dis = cur - i;
		}
	}
	if(cur == hasLen && minWidth > dis) {
		minWidth = dis;
		for(i = 1; i < 10; ++i) {
			minArr[i] = disArr[i];
		}
		return;
	}
	for(i = 1; i <= vlen; ++i) {
		if(flagArr[i] || !hasArr[i]) continue;
		flagArr[i] = 1;
		disArr[cur + 1] = i;
		getDis(cur + 1, dis);
		flagArr[i] = 0;
	}
}

void print() {
	int i;
	for(i = 1; i <= hasLen; ++i) {
		if(hasArr[minArr[i]]) {
			printf("%c ", minArr[i] + 'A' - 1, minArr[i]);
		}
	}
	printf("-> %d\n", minWidth);
}

int main() {
	while(scanf("%s", line) == 1 && line[0] != '#') {
		vlen = 0; minWidth = 10; hasLen = 0;
		memset(graph, 0, sizeof(graph));
		memset(disArr, 0, sizeof(disArr));
		memset(flagArr, 0, sizeof(flagArr));
		memset(hasArr, 0, sizeof(hasArr));
		handleGraph();
		getDis(0, 0);
		print();
	}
	return 0;
}
