#include<stdio.h>
#include<string.h>

int n;
int origin[10];
int arrnow[10];
int arrtemp[10];

void printArr(int * arr) {
	for(int i = 0; i < n; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");
} 

// 获取数组中后继不正确的数字个数 
int getErrorNum(int * arr) {
	int num = 0;
	for(int i = 1; i < n; ++i) {
		if(arr[i] != arr[i-1]+1) ++num;
	}
	return num;
} 

// 当前最少需要的移动次数 
int getMinTime(int * arr) {
	int num = getErrorNum(arr);
	if(num % 3) return num / 3 + 1;
	return num / 3;
}

// 移动位置 
void movePos(int start, int end, int pos) {
	memcpy(arrtemp, arrnow, sizeof(arrnow));
	int movelen = end-start + 1;
	int i, j, k;
	if(start > pos) {
		for(i = 0; i < movelen; ++i)
		arrnow[pos + i] = arrtemp[start + i];
		for(i = 0; i < pos; ++i)
			arrnow[i] = arrtemp[i];
		for(i = pos; i < start; ++i)
			arrnow[i + movelen] = arrtemp[i];
		for(i = end+1; i < n; ++i)
			arrnow[i] = arrtemp[i];
	}
	if(end < pos) {
		for(i = 0; i < movelen; ++i)
			arrnow[pos + i - movelen] = arrtemp[start + i];
		for(i = 0; i < start; ++i)
			arrnow[i] = arrtemp[i];
		for(i = end+1; i < pos; ++i)
			arrnow[i-movelen] = arrtemp[i];
		for(i = pos; i < n; ++i)
			arrnow[i] = arrtemp[i];
	}
}

// 恢复之前移动的位置 
void restorePos(int start, int end, int pos) {
	int movelen = end-start + 1;
	if(start > pos)
		movePos(pos, pos + movelen - 1, start + movelen);
	if(end < pos)
		movePos(pos - movelen, pos-1, start);
}

// 每一轮迭代
bool handleTime(int num, int len) {
	// 到达终点 
	if(num == len) {
		if(!getErrorNum(arrnow)) return true;
		return false;
	}
	// 继续迭代 
	int i, j, k, numnow;
	for(int i = 0; i < n; ++i) {
		if(i != 0 && arrnow[i-1] == arrnow[i]-1) continue;
		for(j = i; j < n; ++j) {
			if(j != n-1 && arrnow[j+1] == arrnow[j]+1) continue;
			for(k = 0; k <= n; ++k) {
				if(k >= i-1 && k <= j+1) continue;
				// 移动
				movePos(i, j, k);
				numnow = num + 1;
				// 剪枝
				if((getMinTime(arrnow) <= (len - numnow))) {
					// 递归
					if(handleTime(numnow, len)) return true;
				}
				// 恢复
				restorePos(i, j, k);
			}
		}
	}
	return false;
}

// 处理入口 
int handle() {
	int i, j;
	for(i = getMinTime(origin); i < 8; ++i) {
		memcpy(arrnow, origin, sizeof(arrnow));
		// 每一轮加深迭代
		if(handleTime(0, i)) return i;
	}
	return 8; 
}

int main() {
	int t = 0;
	int i, j;
	while(scanf("%d\n", &n) == 1 && n > 0) {
		++t;
		for(i = 0; i < n; ++i)
			scanf("%d", &origin[i]);
		j = handle();
		printf("Case %d: %d\n", t, j);
	}
	return 0;	
}
