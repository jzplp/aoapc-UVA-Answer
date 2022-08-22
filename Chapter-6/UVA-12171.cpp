#include<stdio.h>
#include<string.h>
#include<map>
#include<queue>
using namespace std;
 
#define MAXN 505
#define MAXM 105

const int stepX[6] = {1,-1,0,0,0,0}; 
const int stepY[6] = {0,0,1,-1,0,0}; 
const int stepZ[6] = {0,0,0,0,1,-1}; 

struct Box {
	int x0, y0, z0;
	int x, y, z; 
};

struct Point {
	int x, y, z;
}; 

Box arrBox[55];
int boxlen;

int axisX[MAXM];
int axisY[MAXM];
int axisZ[MAXM];
int lenx, leny, lenz;

int space[MAXM][MAXM][MAXM];
bool findSpace[MAXM][MAXM][MAXM];
int volume, area;

void clear() {
	memset(arrBox, 0, sizeof(arrBox));
	boxlen = 0;
	memset(axisX, 0, sizeof(axisX));
	memset(axisY, 0, sizeof(axisY));
	memset(axisZ, 0, sizeof(axisZ));
	lenx = 0;
	leny = 0;
	lenz = 0;
	memset(space, 0, sizeof(space));
	volume = 0;
	area= 0; 
	memset(findSpace, 0, sizeof(findSpace));
}

void input() {
	int i;
	Box b;
	scanf("%d", &boxlen);
	for(i = 0; i < boxlen; ++i) {
		scanf("%d %d %d %d %d %d", &b.x0, &b.y0, &b.z0, &b.x, &b.y, &b.z);
		b.x += b.x0;
		b.y += b.y0;
		b.z += b.z0;
		arrBox[i] = b;
	}
}

void handleAxis() {
	map<int, int> mpx, mpy, mpz;
	int i, j;
	for(i = 0; i < boxlen; ++i) {
		mpx[arrBox[i].x0] = 1;
		mpx[arrBox[i].x] = 1;
		mpy[arrBox[i].y0] = 1;
		mpy[arrBox[i].y] = 1;
		mpz[arrBox[i].z0] = 1;
		mpz[arrBox[i].z] = 1;
	}
	i = 1;
	for(auto ip = mpx.begin(); ip != mpx.end(); ++ip, ++i) {
		mpx[ip->first] = i;
		axisX[i] = ip->first;
	}
	lenx = i;
	axisX[lenx] = MAXN;
	axisX[lenx + 1] = MAXN;
	i = 1;
	for(auto ip = mpy.begin(); ip != mpy.end(); ++ip, ++i) {
		mpy[ip->first] = i;
		axisY[i] = ip->first;
	}
	leny = i;
	axisY[leny] = MAXN; 
	axisY[leny + 1] = MAXN;
	i = 1;
	for(auto ip = mpz.begin(); ip != mpz.end(); ++ip, ++i) {
		mpz[ip->first] = i;
		axisZ[i] = ip->first;
	}
	lenz = i;
	axisZ[lenz] = MAXN;
	axisZ[lenz + 1] = MAXN;
	for(i = 0; i < boxlen; ++i) {
		arrBox[i].x0 = mpx[arrBox[i].x0];
		arrBox[i].x = mpx[arrBox[i].x];
		arrBox[i].y0 = mpy[arrBox[i].y0];
		arrBox[i].y = mpy[arrBox[i].y];
		arrBox[i].z0 = mpz[arrBox[i].z0];
		arrBox[i].z = mpz[arrBox[i].z];
	}
}

bool isEdge(int a) {
	return a / 1000 == 1;
} 

void handleSpace() {
	int i, j, k, a;
	for(a = 0; a < boxlen; ++a) {
		for(i = arrBox[a].x0; i <= arrBox[a].x; ++i) {
			for(j = arrBox[a].y0; j <= arrBox[a].y; ++j) {
				for(k = arrBox[a].z0; k <= arrBox[a].z; ++k) {
					if(i == arrBox[a].x || j == arrBox[a].y || k == arrBox[a].z) {
						if(space[i][j][k] != 1) {
							space[i][j][k] = 1001;
							continue;
						}
					}
					space[i][j][k] = 1;
				}
			}
		}
	}
}

void getBorder() {
	Point p;
	int i, a, b, c;
	queue<Point> qu;
	space[0][0][0] = 2;
	qu.push({0, 0, 0});
	while(!qu.empty()) {
		p = qu.front();
		qu.pop();
		for(i = 0; i < 6; ++i) {
			a = p.x + stepX[i];
			b = p.y + stepY[i];
			c = p.z + stepZ[i];
			if(a < 0 || a > lenx || b < 0 || b > leny || c < 0 || c > lenz) continue;
			if(space[a][b][c] % 1000 == 2) continue;
			if(space[a][b][c] == 0) space[a][b][c] = 2;
			if(isEdge(space[a][b][c])) space[a][b][c] = 1002;
			if(space[a][b][c] % 1000 == 2)
				qu.push({a, b, c}); 
		}
	}
}

int getVolumeOne(int a, int b, int c) {
	return (axisX[a+1] - axisX[a]) * (axisY[b+1] - axisY[b]) * (axisZ[c+1] - axisZ[c]);
}

int getAreaOne(int a, int b, int c) {
	int sum = 0;
	if(isEdge(space[a][b][c])) {
		if(space[a-1][b][c] == 1) {
			sum += (axisY[b+1] - axisY[b]) * (axisZ[c+1] - axisZ[c]);
		}
		if(space[a][b-1][c] == 1) {
			sum += (axisX[a+1] - axisX[a]) * (axisZ[c+1] - axisZ[c]);
		}
		if(space[a][b][c-1] == 1) {
			sum += (axisX[a+1] - axisX[a]) * (axisY[b+1] - axisY[b]);
		}
	}
	if(space[a][b][c] == 1) {
		if(space[a-1][b][c] % 1000 == 2) {
			sum += (axisY[b+1] - axisY[b]) * (axisZ[c+1] - axisZ[c]);
		}
		if(space[a][b-1][c] % 1000 == 2) {
			sum += (axisX[a+1] - axisX[a]) * (axisZ[c+1] - axisZ[c]);
		}
		if(space[a][b][c-1] % 1000 == 2) {
			sum += (axisX[a+1] - axisX[a]) * (axisY[b+1] - axisY[b]);
		}
	}
	return sum;
}

void getVolumeAndArea() {
	volume = 0;
	area = 0;
	Point p;
	int i, a, b, c;
	queue<Point> qu;
	findSpace[0][0][0] = true;
	volume += getVolumeOne(0, 0, 0);
	qu.push({0, 0, 0});
	while(!qu.empty()) {
		p = qu.front();
		qu.pop();
		for(i = 0; i < 6; ++i) {
			a = p.x + stepX[i];
			b = p.y + stepY[i];
			c = p.z + stepZ[i];
			if(a < 0 || a >= lenx || b < 0 || b >= leny || c < 0 || c >= lenz) continue;
			if(findSpace[a][b][c]) continue;
			findSpace[a][b][c] = true;
			if(space[a][b][c] == 1 || space[a][b][c] == 1002) {
				area += getAreaOne(a, b, c);
			}
			if(space[a][b][c] % 1000 == 2) {
				volume += getVolumeOne(a, b, c);
				qu.push({a, b, c});
			}
		}
	}
}

void outputValue() {
	int i, j ,k;
	for(i = 0; i <= lenx; ++i) {
		printf("%d ", axisX[i]);
	}
	putchar('\n');
	for(i = 0; i <= leny; ++i) {
		printf("%d ", axisY[i]);
	}
	putchar('\n');
	for(i = 0; i <= lenz; ++i) {
		printf("%d ", axisZ[i]);
	}
	putchar('\n');
	
	for(i = 0; i <= lenx; ++i) {
		for(j = 0; j <= leny; ++j) {
			for(k = 0; k <= lenz; ++k) {
				printf("%d %d %d %d\n", i, j, k, space[i][j][k]);
			}
		}
	}
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		clear();
		input();
		handleAxis();
		handleSpace(); 
		getBorder();
		getVolumeAndArea();
		volume = MAXN * MAXN * MAXN - volume;
		printf("%d %d\n", area, volume);
	}
	return 0;
}
