#include<cstdio>

#define MAXN 12

bool arrh[MAXN][MAXN];
bool arrv[MAXN][MAXN];
int n;

bool judge(int x,int y, int m) {
	int i;
	for(i=x;i<(x+m);++i) {
		if(arrv[i][y] == false)
			return false;
		if(arrv[i][y+m] == false)
			return false;
	}
	for(i=y;i<(y+m);++i) {
		if(arrh[x][i] == false)
			return false;
		if(arrh[x+m][i] == false)
			return false;
	}
	//printf("--- %d %d %d\n", x,y,m);
	return true;
}

int squareNum(int m) {
	int i,j,k=0;
	for(i=1; i<=(n-m); ++i)
		for(j=1; j<=(n-m); ++j)
			if(judge(i, j, m))
				++k;
	return k;
}

int main() {
	int m,i,j,k=0;
	char c;
	while(scanf("%d %d", &n, &m) == 2) {
		for(i=1; i<=n; ++i)
			for(j=1; j<=n; ++j) {
				arrh[i][j] = false;
				arrv[i][j] = false;
			}
		while(m--) {
			scanf(" %c %d %d", &c, &i, &j);
			if(c == 'H')
				arrh[i][j] = true;
			else
				arrv[j][i] = true;
		}
		if(k!=0)
			puts("\n**********************************\n");
		printf("Problem #%d\n\n", ++k);
		c = 0;
		for(i=1; i<n; ++i) {
			j = squareNum(i);
			if(j != 0) {
				c = 1;
				printf("%d square (s) of size %d\n", j, i);
			}
		}
		if(c == 0)
			puts("No completed squares can be found.");
	}
	return 0;
}
