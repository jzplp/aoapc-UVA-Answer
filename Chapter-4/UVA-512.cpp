#include<cstring>
#include<algorithm>
#include<string>
#include<cstdio>
using namespace std;

#define MAXN 55
struct Cell {
	int x,y;
};
Cell arr[MAXN][MAXN];
int arr1[MAXN];
char ss[10];
int r,c,k;

void INI() {
	int i,j;
	for(i=1; i<=r; ++i)
		for(j=1; j<=c; ++j)
			arr[i][j] = (Cell) {i,j};
}

void EX() {
	int x,y,xi,yi;
	int x1,y1,x2,y2,i,j;
	scanf("%d %d %d %d", &x, &y, &xi, &yi);
	for(i=1;i<=r;++i)
		for(j=1;j<=c;++j) {
			if(arr[i][j].x == x && arr[i][j].y == y) {
				x1 = i;
				y1 = j;
			}
			if(arr[i][j].x == xi && arr[i][j].y == yi) {
				x2 = i;
				y2 = j;
			}
		}
	swap(arr[x1][y1], arr[x2][y2]);
}

void I(int t) {
	int i,j,ii;
	for(ii=k-1;ii>=0;--ii) {
		for(i=1;i<=r;++i) {
			for(j=1;j<=c;++j) {
				if(t == 1 && arr[i][j].y >= arr1[ii]) {
					arr[i][j].y += 1;
					continue;
				}
				if(t == 2 && arr[i][j].x >= arr1[ii]) {
					arr[i][j].x += 1;
					continue;
				}
				if(t == 3) {
					if(arr[i][j].y == arr1[ii]) {
						arr[i][j].x = 0;
						arr[i][j].y = 0;
						continue;
					}
					if(arr[i][j].y > arr1[ii])
						arr[i][j].y -= 1;
					continue;
				}
				if(t == 4) {
					if(arr[i][j].x == arr1[ii]) {
						arr[i][j].x = 0;
						arr[i][j].y = 0;
						continue;
					}
					if(arr[i][j].x > arr1[ii])
						arr[i][j].x -= 1;
				}
			}
		}
	}
}

int main() {
	int x,y,i,j,ri,ci,t,tt=0;
	string s;
	while(scanf("%d %d", &r, &c) == 2 && r != 0) {
		printf("Spreadsheet #%d\n", ++tt);
		INI();
		scanf("%d", &t);
		while(t--) {
			scanf("%s", ss);
			s = ss;
			if(s == "EX") {
				EX();
				continue;
			}
			scanf("%d", &k);
			for(i=0;i<k;++i)
				scanf("%d", arr1+i);
			sort(arr1, arr1+k);
			if(s == "IC")
				I(1);
			if(s == "IR")
				I(2);
			if(s == "DC")
				I(3);
			if(s == "DR")
				I(4);
		}
		scanf("%d", &t);
		while(t--) {
			scanf("%d %d", &x, &y);
			printf("Cell data in (%d,%d) ", x, y);
			if(arr[x][y].x == 0)
				puts("GONE");
			else
				printf("moved to (%d,%d)\n", arr[x][y].x, arr[x][y].y);
		}
	}
	return 0;
}
