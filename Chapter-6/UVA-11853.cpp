#include<stdio.h>
#include<string.h>
#include<math.h>
#define MAXN 1005

int n;
struct Circle {
	double x, y, range;
};
Circle arrCir[MAXN];
int vis[MAXN];
double leftPoint, rightPoint;

void clear() {
	memset(arrCir, 0, sizeof(arrCir));
	memset(vis, 0, sizeof(vis));
	leftPoint = 1000, rightPoint = 1000;
}

bool contact(int i, int j) {
	double dis1 = (arrCir[i].x - arrCir[j].x) * (arrCir[i].x - arrCir[j].x) + (arrCir[i].y - arrCir[j].y) * (arrCir[i].y - arrCir[j].y);
	double dis2 = (arrCir[i].range + arrCir[j].range) * (arrCir[i].range + arrCir[j].range);
	return dis1 < dis2;
}

void calEdge(int i) {
	if(arrCir[i].x <= arrCir[i].range) {
		double dis = arrCir[i].y - sqrt(arrCir[i].range * arrCir[i].range - arrCir[i].x * arrCir[i].x);
		if(dis < leftPoint) leftPoint = dis;
	}
	if(arrCir[i].x + arrCir[i].range >= 1000) {
		double dis = arrCir[i].y - sqrt(arrCir[i].range * arrCir[i].range - (1000 - arrCir[i].x) * (1000 - arrCir[i].x));
		if(dis < rightPoint) rightPoint = dis;
	}
}

bool dfs(int i) {
	vis[i] = 1;
	if(arrCir[i].y <= arrCir[i].range) {
		return true;
	}
	int j;
	for(j = 0; j < n; ++j) {
		if(!vis[j] && contact(i, j)) {
			if(dfs(j)) {
				return true;
			}
		}
	}
	calEdge(i);
	return false;
}

bool handle() {
	int i;
	for(i = 0; i < n; ++i) {
		if(!vis[i] && arrCir[i].y + arrCir[i].range >= 1000) {
			if(dfs(i)) {
				return true;
			}
		}
	}
	return false; 
}

int main() {
	int i;
	double x, y, range;
	while(scanf("%d", &n) > 0) {
		clear();
		for(i = 0; i < n; ++i) {
			scanf("%lf %lf %lf", &x, &y, &range);
			arrCir[i] = {x, y, range};
		}
		if(handle()) {
			printf("IMPOSSIBLE\n");
		} else {
			printf("%.2lf %.2lf %.2lf %.2lf\n", 0.0, leftPoint, 1000.0, rightPoint);
		}
	}
	return 0;
}
 
