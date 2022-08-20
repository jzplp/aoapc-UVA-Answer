#include<stdio.h>
#include<string.h>
#include<queue>

#define MAXN 12
using namespace std;

const int LT[4] = {-1, 0, 1, 0};
const int RT[4] = {0, 1, 0, -1};

struct NodePath {
	int l, r;
	int dir, dirold;
};

// 结点来源
NodePath prevArr[MAXN][MAXN][5];
// 结点允许走的路 
bool pathArr[MAXN][MAXN][5][5];

int begl, begr, endl, endr, dirbeg;

int dir2int(char c) {
	switch(c) {
		case 'N': return 0;
		case 'E': return 1;
		case 'S': return 2;
		case 'W': return 3;
	}
}

int turn2int(char c) {
		switch(c) {
		case 'F': return 0;
		case 'L': return 3;
		case 'R': return 1;
	}
}

void inputNodes() {
	int l, r, dir;
	int i, j;
	char s[10];
	while(1) {
		scanf("%d %d", &l, &r);
		if(l == 0) {
			break;
		}
		while(scanf("%s", s) > 0) {
			if(s[0] == '*') {
				break;
			}
			dir = dir2int(s[0]);
			for(i = 1; s[i] != 0; ++i) {
				pathArr[l][r][dir][turn2int(s[i])] = true;
			}
		}
	}
}

void clear() {
	memset(prevArr, 0, sizeof(prevArr));
	memset(pathArr, 0, sizeof(pathArr));
	begl = 0;
	begr = 0;
	endl = 0;
	endr = 0;
}

NodePath createNodePath(int l ,int r, int dir, int i) {
	NodePath np;
	np.l = l + LT[(dir + i) % 4];
	np.r = r + RT[(dir + i) % 4];
	np.dir = (dir + i) % 4;
	np.dirold = dir;
	return np;
} 

NodePath count(int dir) {
	queue<NodePath> qu;
	int i, j, k;
	qu.push(createNodePath(begl, begr, dir, 0));
	while(!qu.empty()) {
		NodePath np = qu.front();
		qu.pop();
		if(np.l == endl && np.r == endr) {
			return np;
		}
		for(i = 0; i < 4; ++i) {
			if(pathArr[np.l][np.r][np.dir][i]) {
				NodePath npw = createNodePath(np.l, np.r, np.dir, i);
				if(prevArr[npw.l][npw.r][npw.dir].l) {
					continue;
				}
				prevArr[npw.l][npw.r][npw.dir] = np; 
				qu.push(npw);
			}
		}
	}
	return {0, 0, 0, 0};
}

NodePath getPrevPath(NodePath np) {
	np = prevArr[np.l][np.r][np.dir];
	return np;
}

void countRouter(vector<NodePath> &v, NodePath np) {
	while(np.l != 0 && (np.l != begl || np.r != begr || np.dir != dirbeg || np.dirold != dirbeg)) {
		v.push_back(np);
		np = getPrevPath(np);
	}
	v.push_back({
		begl, begr
	});
}

void output(vector<NodePath> &v) {
	NodePath np;
	int i, j;
	for(i = 0; i < v.size() / 2; ++i) {
		np = v[i];
		v[i] = v[v.size() - i - 1];
		v[v.size() - i - 1] = np;
	}
	printf("  ");
	for(i = 0; i < v.size(); ++i) {
		if(i != 0 && i % 10 == 0) {
			printf("\n ");
		}
		if(i != 0) {
			putchar(' ');
		}
		printf("(%d,%d)", v[i].l, v[i].r);
	}
	printf("\n");
}

int main() {
	char s[30];
	char dir[10];
	while(scanf("%s", s) > 0) {
		if(strcmp(s, "END") == 0) {
			break;
		}
		clear();
		scanf("%d %d %s %d %d", &begl, &begr, dir, &endl, &endr);
		dirbeg = dir2int(dir[0]);
		inputNodes();
		printf("%s\n", s);
		NodePath np = count(dirbeg);
		if(np.l == 0) {
			printf("  No Solution Possible\n");
			continue;
		}
		vector<NodePath> v;
		countRouter(v, np);
		output(v);
	}
	return 0;
} 
