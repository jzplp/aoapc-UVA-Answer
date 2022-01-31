#include<stdio.h>
#include<vector>
#include<iostream>
#include<string>
#include<sstream>

using namespace std;
vector<int> v[26];
int n;

struct pos {
	int x, y;
};


void show() {
	int i, j;
	for(i = 0; i < n; ++i) {
		printf("%d:", i);
		for(j = 0; j < v[i].size(); ++j) {
			printf(" %d", v[i][j]);
		}
		putchar('\n');
	}
}

pos findpos(int a) {
	pos p = {0, 0};
	int i, j;
	for(i =0; i < n; ++i) {
		for(j = 0; j < v[i].size(); ++j) {
			if(v[i][j] == a) {
				p.x = i;
				p.y = j;
				return p;
			}
		}
	}
	return p;
} 

bool inipos(pos p, int bx) {
	int i, j;
	bool bb = false;
	vector<int> vp = v[p.x];
	v[p.x].resize(p.y);
	for(i = p.y+1; i < vp.size(); ++i) {
		if(vp[i] == bx) {
			bb = true;
			continue;
		}
		v[vp[i]].push_back(vp[i]);
	}
	return bb;
}


void moveonto(int a, int b) {
	pos pa = findpos(a);
	pos pb = findpos(b);
	if(pa.x == pb.x) {
		return;
	}
	bool ba = inipos(pa, pb.x), bb = inipos(pb, pb.x);
	bb = ba && bb;
	v[pb.x].push_back(b);
	v[pb.x].push_back(a);
	if(bb) {
		v[pb.x].push_back(pb.x);
	}
}

void moveover(int a, int b) {
	pos pa = findpos(a);
	pos pb = findpos(b);
	if(pa.x == pb.x) {
		return;
	}
	bool bb = inipos(pa, pb.x);
	v[pb.x].push_back(a);
	if(bb) {
		v[pb.x].push_back(pb.x);
	}
}

void pileonto(int a, int b) {
	int i;
	pos pa = findpos(a);
	pos pb = findpos(b);
	if(pa.x == pb.x) {
		return;
	}
	vector<int> vp = v[pb.x];
	v[pb.x].resize(pb.y + 1);
	for(i = pa.y; i < v[pa.x].size(); ++i) {
		v[pb.x].push_back(v[pa.x][i]);
	}
	v[pa.x].resize(pa.y);
	for(i = pb.y+1; i < vp.size(); ++i) {
		v[vp[i]].push_back(vp[i]);
	}
}

void pileover(int a, int b) {
	int i;
	pos pa = findpos(a);
	pos pb = findpos(b);
	if(pa.x == pb.x) {
		return;
	}
	for(i = pa.y; i < v[pa.x].size(); ++i) {
		v[pb.x].push_back(v[pa.x][i]);
	}
	v[pa.x].resize(pa.y);
}

int main() {
	int a, b;
	int i, j, k;
	string line, word1, word2;
	while(scanf("%d", &n) == 1) {
		for(i = 0; i < n; ++i) {
			v[i].clear();
			v[i].push_back(i);
		}
		while(1) {
			cin >> line;
			istringstream is(line);
			is >> word1;
			if(word1 == "quit") {
				break;
			}
			cin >> a >> word2 >> b;
			if(a == b) {
				continue;
			}
			if(word1 == "move" && word2 == "onto") {
				moveonto(a, b);
			}
			if(word1 == "move" && word2 == "over") {
				moveover(a, b);
			}
			if(word1 == "pile" && word2 == "onto") {
				pileonto(a, b);
			}
			if(word1 == "pile" && word2 == "over") {
				pileover(a, b);
			}
			// show();
		}
		show();
	}
	return 0;
}
