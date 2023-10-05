#include<stdio.h>
#include<string>
#include<string.h>
#include<set>

using namespace std;

int n, w, h;
int steps[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
// 数量
int num;
set<int> seArr, seTemp;
set<set<int>> se;
int arrTemp[10][2];
// 该状态是否访问过 
set<set<int>> seFlag;

int tenTable[1000] = {0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,16,68,108,117,118,0,0,0,21,277,842,1226,1329,1338,1339,0,0,21,287,1847,3234,3773,3876,3885,3886,0,1,277,1847,2376,4003,4542,4645,4654,4655,0,16,842,3234,4003,4003,4542,4645,4654,4655,0,68,1226,3773,4542,4542,4542,4645,4654,4655,0,108,1329,3876,4645,4645,4645,4645,4654,4655,0,117,1338,3885,4654,4654,4654,4654,4654,4655,1,118,1339,3886,4655,4655,4655,4655,4655,4655};


void getXY(int res, int &x, int &y) {
	x = res / 100 - 20;
	y = res % 100 - 20;
}

void output(set<int> &setTemp) {
	int x, y;
	for(auto ip = setTemp.begin(); ip != setTemp.end(); ++ip) {
		getXY(*ip, x, y);
		printf("[%d,%d] ", x, y);
	}
	putchar('\n');
}

int setXY(int x, int y) {
	return (x + 20) * 100 + y + 20;
}

// 规范化 最小的x为 1 最小的y为 1
void standard(int (* arr)[2], int ntemp) {
	int i;
	int minX = arr[0][0], minY = arr[0][1];
	for(i = 1; i < ntemp; ++i) {
		if(arr[i][0] < minX) minX = arr[i][0];
		if(arr[i][1] < minY) minY = arr[i][1];
	}
	for(i = 0; i < ntemp; ++i) {
		if(arr[i][0] * minX > 0)
			arr[i][0] = arr[i][0] - minX + 1;
		else
			arr[i][0] = arr[i][0] - minX;
		if(arr[i][1] * minY > 0)
			arr[i][1] = arr[i][1] - minY + 1;
		else
			arr[i][1] = arr[i][1] - minY;
	}
}

// 点的数组转为set 
void arr2Set(set<int> &setTemp, int (* arr)[2], int ntemp) {
	setTemp.clear();
	for(int i = 0; i < ntemp; ++i) {
		setTemp.insert(setXY(arr[i][0], arr[i][1]));
	}
}

// set转为点的数组
void set2Arr(set<int> &setTemp, int (* arr)[2]) {
	int i = 0;
	for(auto ip = setTemp.begin(); ip != setTemp.end(); ++ip, ++i) {
		getXY(*ip, arr[i][0], arr[i][1]);
	}
}

// 向右旋转90度
void turnRight(int (* arr)[2], int ntemp) {
	int j;
	for(int i = 0; i < ntemp; ++i) {
		j = arr[i][1];
		arr[i][1] = -arr[i][0];
		arr[i][0] = j;
	}
}

// 镜像反转
void reserveArr(int (* arr)[2], int ntemp) {
	for(int i = 0; i < ntemp; ++i) {
		arr[i][0] = -arr[i][0]; 
	}
}

void judge(set<int> &setTemp) {
	if(se.count(setTemp)) return;
	++num;
	se.insert(seTemp);
}

bool isBumpWall(set<int> &setTemp) {
	auto ip = setTemp.begin();
	int x, y;
	getXY(*ip, x, y);
	int minX = x, minY = y, maxX = x, maxY = y;
	for(ip = setTemp.begin(); ip != setTemp.end(); ++ip) {
		getXY(*ip, x, y);
		if(x < minX) minX = x;
		if(y < minY) minY = y;
		if(x > maxX) maxX = x;
		if(y > maxY) maxY = y;
	}
	x = maxX - minX - (maxX * minX < 0 ? 1 : 0);
	y = maxY - minY - (maxY * minY < 0 ? 1 : 0);
	if(((x >= w || y >= h) && (x >= h || y >= w)) || x + y >= n) return true;
	return false; 
} 

// 该模式的几种变形是否访问过 
bool findModel(int (* arr)[2], set<int> &setTemp, int ntemp) {
	if(seFlag.count(setTemp)) return true;
	int i;
	for(i = 0; i < 3; ++i) {
		// 转90度
		turnRight(arrTemp, ntemp);
		standard(arrTemp, ntemp);
		arr2Set(setTemp, arrTemp, ntemp);
		if(seFlag.count(setTemp)) return true;
	}
	// 镜像反转
	reserveArr(arrTemp, ntemp);
	for(i = 0; i < 4; ++i) {
		// 转90度
		if(i != 0) turnRight(arrTemp, ntemp);
		standard(arrTemp, ntemp);
		arr2Set(setTemp, arrTemp, ntemp);
		if(seFlag.count(setTemp)) return true;
	}
	return false; 
}

void dfs(int count) {
	++count;
	int i, x, y, xi, yi, resi;
	for(auto ip = seArr.begin(); ip != seArr.end(); ++ip) {
		getXY(*ip, x, y);
		for(i = 0; i < 4; ++i) {
			xi = steps[i][0] + x;
			yi = steps[i][1] + y;
			if(xi == 0) {
				if(steps[i][0] > 0) xi = 1;
				if(steps[i][0] < 0) xi = -1;
			}
			if(yi == 0) {
				if(steps[i][1] > 0) yi = 1;
				if(steps[i][1] < 0) yi = -1;
			}
			resi = setXY(xi, yi);
			if(seArr.count(resi)) continue;
			seArr.insert(resi);
			set2Arr(seArr, arrTemp);
			standard(arrTemp, count);
			arr2Set(seTemp, arrTemp, count);
			if(!isBumpWall(seArr) && !findModel(arrTemp, seTemp, count)) {
				// 设置访问标记 
				seFlag.insert(seTemp);
				if(count == n) judge(seTemp);
				else dfs(count);
			}
			seArr.erase(resi);
		}
	}
}

int compute() {
	num = 0;
	se.clear();
	seFlag.clear();
	seArr.clear();
	seArr.insert(setXY(1, 1));
	dfs(1);
	return num;
}

int main() {
	while(scanf("%d %d %d", &n, &w, &h) == 3) {
		if(w * h < n) {
			printf("0\n");
			continue;
		}
		if(w * h == n || n == 1) {
			printf("1\n");
			continue;
		}
		if(n == 10) {
			printf("%d\n", tenTable[(w-1)*10 + h-1]);
			continue;
		}
		printf("%d\n", compute());
	}
	return 0;
}
