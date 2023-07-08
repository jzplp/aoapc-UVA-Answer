#include<string>
#include<string.h>
#include<iostream>
#include<vector>
using namespace std;

struct PATH {
	int p;
	int top, face;
};

int graph[12][12];
vector<PATH> path[12][12]; 
int row, column;
int startr, startc;
bool flag, startFlag;
// 下 右 上 左
int Step[5][2] = {{}, {1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int pathArr[110][2];
int pathLen;

// 顺时针 上 右 下 左 背 
int Die[7][5] = {
{},
{5, 3, 2, 4, 6},
{1, 3, 6, 4, 5},
{1, 5, 6, 2, 4},
{6, 5, 1 ,2, 3},
{3, 1, 4, 6, 2},
{3, 5, 4, 2, 1},
};

bool judgeStep(int r, int c) {
	if(r <= 0 || r > row) return false;
	if(c <= 0 || c > column) return false;
	return true;
}

void getDieStatus(int top, int face, int step, int *topn, int *facen) {
	// 顺着放的 
	if(Die[face][0] == top) {
		switch(step) {
			case 1:
				*facen = Die[face][0];
				*topn = Die[face][4];
				break;
			case 2:
				*facen = face;
				*topn = Die[face][3];
				break;
			case 3:
				*facen = Die[face][2];
				*topn = face;
				break;
			case 4:
				*facen = face;
				*topn = Die[face][1];
				break;
		}
		return;
	}
	if(Die[face][2] == top) {
		// 逆着放的
		switch(step) {
			case 1:
				*facen = Die[face][2];
				*topn = Die[face][4];
				break;
			case 2:
				*facen = face;
				*topn = Die[face][1];
				break;
			case 3:
				*facen = Die[face][0];
				*topn = face;
				break;
			case 4:
				*facen = face;
				*topn = Die[face][3];
				break;
		}
		return;
	}
	if(Die[face][3] == top) {
		// 左侧的当顶
		switch(step) {
			case 1:
				*facen = Die[face][3];
				*topn = Die[face][4];
				break;
			case 2:
				*facen = face;
				*topn = Die[face][2];
				break;
			case 3:
				*facen = Die[face][1];
				*topn = face;
				break;
			case 4:
				*facen = face;
				*topn = Die[face][0];
				break;
		}
		return;
	}
	if(Die[face][1] == top) {
		// 左侧的当顶
		switch(step) {
			case 1:
				*facen = Die[face][1];
				*topn = Die[face][4];
				break;
			case 2:
				*facen = face;
				*topn = Die[face][0];
				break;
			case 3:
				*facen = Die[face][3];
				*topn = face;
				break;
			case 4:
				*facen = face;
				*topn = Die[face][2];
				break;
		}
		return;
	}
}

bool judgePath(int r, int c, int step, int top, int face) {
	for(int i = 0; i < path[r][c].size(); ++i) {
		if(path[r][c][i].top == top && path[r][c][i].face == face) return false;
	}
	return true;
}

void work(int r, int c, int top, int face) {
	if(startFlag && r == startr && c == startc) {
		flag = true;
		return;
	}
	startFlag = true;
	// cout << r << " " << c << endl;
	int i, j, rn, cn, topn, facen; 
	for(i = 1; i < 5; ++i) {
		rn = r + Step[i][0];
		cn = c + Step[i][1];
		if(!judgeStep(rn, cn)) continue;
		if(flag) return;
		if(graph[rn][cn] != -1 && graph[rn][cn] != top) continue;
		getDieStatus(top, face, i, &topn, &facen);
		if(!judgePath(rn, cn, i, topn, facen)) continue;
		path[rn][cn].push_back({i, topn, facen});
		work(rn, cn, topn, facen);
		if(flag) return;
		path[rn][cn].pop_back();
	}
}

void getPathArr() {
	int r, c, rn, cn;
	int i, j, k, step;
	pathLen = 0;
	r = startr, c = startc;
	do {
		pathArr[pathLen][0] = r;
		pathArr[pathLen][1] = c;
		++pathLen;
		step = path[r][c][path[r][c].size() - 1].p;
		rn = r-Step[step][0];
		cn = c-Step[step][1];
		// cout << path[r][c].size() - 1 << "  " << rn << " " << cn << endl;
		path[r][c].pop_back();
		r = rn;
		c = cn;
	} while(r != startr || c != startc);
	pathArr[pathLen][0] = r;
	pathArr[pathLen][1] = c;
	++pathLen;
}

int main() {
	string line;
	int top, face;
	int i, j, k;
	while(cin >> line && line != "END") {
		cout << line << endl;
		cin >> row >> column >> startr >> startc >> top >> face;
		for(i = 1; i <= row; ++i) {
			for(j = 1; j <= column; ++j) {
				 cin >> graph[i][j];
				 path[i][j] = vector<PATH>();
			}
		}
		flag = false; startFlag = false;
		work(startr, startc, top, face);
		if(!flag) {
			cout << "  No Solution Possible" << endl;
			continue;
		}
		getPathArr();
		cout << "  ";
		for(i = 1; i <= pathLen; ++i) {
			cout << "(" << pathArr[pathLen-i][0] << "," << pathArr[pathLen-i][1] << ")";
			if(i != pathLen) cout << ",";
			if(i % 9 == 0 && i != pathLen) cout << endl << "  ";
		}
		cout << endl;
	}
	return 0;
} 
