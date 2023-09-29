#include<stdio.h>
#include<string.h>
#include<math.h>

int n, maxCount;
int setArr[1010];
int maxV;

int getMin(int a, int b) {
	if(a > b) return b;
	return a;
}

// µ›πÈ±È¿˙ 
bool dfs(int count, int pre, int subCount) {
	if(pre == n) return true;
	if(count >= maxCount) return false;
	if(maxV * (1 << (maxCount - count)) < n) return false;
	if(subCount > 2) return false;
	int value, preMaxV, i;
	if(pre < n) {
		for(i = getMin(maxV, n); i > 0; --i) {
			if(!setArr[i]) continue;
			value = i + pre;
			if(value > 1000 || (value > n && maxV > n)) continue;
			if(setArr[value]) continue;
			setArr[value] = 1;
			preMaxV = maxV;
			if(value > maxV) maxV = value;
			if(dfs(count+1, value, subCount)) return true;
			setArr[value] = 0;
			maxV = preMaxV; 
		}
	}
	if(subCount == 2) return false;
	for(i = maxV; i > 0; --i) {
		if(!setArr[i]) continue;
		value = abs(i - pre);
		if(value == 0 || value > n) continue;
		if(value == n) return true;
		if(setArr[value]) continue;
		setArr[value] = 1;
		if(dfs(count+1, value, subCount + 1)) return true;
		setArr[value] = 0;
	}
	return false;
}

// ≥ı ºªØ 
int computed() {
	if(n == 1) return 0;
	for(maxCount = 1; maxCount < 20; ++maxCount) {
		memset(setArr, 0, sizeof(setArr));
		setArr[1] = 1;
		maxV = 1;
		if(dfs(0, 1, 0)) return maxCount;
	}
}

int main() {
	while(scanf("%d", &n) == 1 && n > 0) {
		printf("%d\n", computed());
	}
	return 0;
}



