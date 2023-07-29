#include<stdio.h>
#include<string.h>

int stones[20];
int s;
double r;

double maxWidth;

struct Node {
	bool enable;
	int weight;
	double left, right;
};
Node arr[50];

double max(double a, double b) {
	if(a > b) return a;
	return b;
}

Node mergeNode(int i, int j) {
	Node no;
	no.enable = true;
	no.weight = arr[i].weight + arr[j].weight;
	double a = (double)arr[i].weight / no.weight;
	double b = (double)arr[j].weight / no.weight;
	no.left = max(b + arr[i].left, arr[j].left - a);
	no.right = max(a + arr[j].right, arr[i].right - b);
	return no;
}

void getValue(int len) {
	int i;
	double value;
	for(i = 0; i < len; ++i) {
		if(arr[i].enable) {
			value = arr[i].left + arr[i].right;
			if(value <= r && value > maxWidth) {
				maxWidth = value;
			}
			return;
		}
	}
}

void cal(int len, int enableLen) {
	int i ,j, k;
	if(enableLen == 1) {
		getValue(len);
	}
	for(i = 0; i < len; ++i) {
		if(!arr[i].enable) continue;
		for(j = i + 1; j < len; ++j) {
			if(!arr[j].enable) continue;
			// 二重循环找到一个组合 区分组合在左边和在右边的场景 
			--enableLen;
			arr[i].enable = false;
			arr[j].enable = false;
			arr[len] = mergeNode(i, j);
			cal(len+1, enableLen);
			arr[len] = mergeNode(j, i);
			cal(len+1, enableLen);
			++enableLen;
			arr[i].enable = true;
			arr[j].enable = true;
		}
	}
}

int main() {
	int n, i;
	scanf("%d", &n);
	while(n--) {
		scanf("%lf %d", &r, &s);
		for(i = 0; i < s; ++i) scanf("%d", &stones[i]);
		if(s == 1) {
			printf("%.16lf\n", 0.0);
			continue;
		}

		maxWidth = -1;
		for(i = 0; i < s; ++i) {
			arr[i] = { true, stones[i], 0, 0 };
		}
		cal(s, s);
		if(maxWidth < 0)
			printf("-1\n");
		else
			printf("%.16lf\n", maxWidth);
	}
	return 0;
}
