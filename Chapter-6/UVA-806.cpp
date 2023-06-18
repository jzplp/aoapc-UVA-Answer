#include<stdio.h>
#include<string.h>
#include<stdlib.h>

bool graphs[70][70];
int paths[4100];
int n, pathNum;

void inGraphs() {
	while(getchar() != '\n') ;
	int i, j, k;
	for(i = 0; i < n; ++i) {
		for(j = 0; j < n; ++j) {
			k = 0;
			scanf("%c", &k);
			if(k == '1') graphs[i][j] = true;
			if(k == '0') graphs[i][j] = false;
		}
		while(getchar() != '\n') ;
	}
}

void handleOnePath(int k) {
	int unit, begx = 0, endx = n, begy = 0, endy = n, ni = n;
	int i, j;
	while(k > 0) {
		unit = k % 5;
		k = k / 5;
		ni = ni / 2;
		switch(unit) {
			case 1:
				endx = begx + ni;
				endy = begy + ni;
				break;
			case 2:
				endx = begx + ni;
				begy = begy + ni;
				break;
			case 3:
				begx = begx + ni;
				endy = begy + ni;
				break;
			case 4:
				begx = begx + ni;
				begy = begy + ni;
				break;
		}
	}
	for(i = begx; i < endx; ++i) {
		for(j = begy; j < endy; ++j) {
			graphs[i][j] = true;
		}
	}
}

void inPaths() {
	int k, i, j;
	while(scanf("%d", &k) && k != -1) {
		if(k == 0) {
			for(i = 0; i < n; ++i) {
				for(j = 0; j < n; ++j) {
					graphs[i][j] = true;
				}
			}
		}
		handleOnePath(k);
	}
}

void outGraphs() {
	int i, j;
	for(i = 0; i < n; ++i) {
		for(j = 0; j < n; ++j) printf("%c", graphs[i][j] == true ? '*' : '.');
		putchar('\n');
	}
}

int handlePaths(int begx, int begy, int unit, int base, int basei) {
	if(unit == 1) {
		if(graphs[begx][begy] == false) return 0; 
		else return 1;
	}
	int cell[4];
	unit = unit / 2;
	cell[0] = handlePaths(begx, 		begy, 			unit, base + basei * 1, basei*5);
	cell[1] = handlePaths(begx, 		begy + unit, 	unit, base + basei * 2, basei*5);
	cell[2] = handlePaths(begx + unit, 	begy, 			unit, base + basei * 3, basei*5);
	cell[3] = handlePaths(begx + unit, 	begy + unit, 	unit, base + basei * 4, basei*5);
	if(cell[0] == 0 && cell[1] == 0 && cell[2] == 0 && cell[3] == 0) return 0;
	if(cell[0] == 1 && cell[1] == 1 && cell[2] == 1 && cell[3] == 1) return 1;
	for(int i = 0; i < 4; ++i) {
		if(cell[i] == 1) paths[pathNum++] = base + basei * (i+1); 
	}
	return 2;
}

void outPaths() {
	int i, j = 0;
	for(i = 0; i < pathNum; ++i) {
		if(j != 0 && j != 12) putchar(' ');
		if(j == 12) {
			putchar('\n');
			j = 0;
		}
		printf("%d", paths[i]);
		++j;
	}
	if(pathNum) putchar('\n');
	printf("Total number of black nodes = %d\n", pathNum);
}

int comp(const void * ltr, const void* rtr) {
	int l = *(const int *)ltr;
	int r = *(const int *)rtr;
	if(l < r) return -1;
	if(l == r) return 0;
	return 1;
}

int main() {
	int t = 0, res;
	while(scanf("%d", &n) && n != 0) {
		if(t) printf("\n");
		printf("Image %d\n", ++t); 
		memset(graphs, 0, sizeof(graphs));
		memset(paths, 0, sizeof(paths));
		pathNum = 0;
		if(n > 0) {
			inGraphs();
			res = handlePaths(0, 0, n, 0, 1);
			if(res == 1) paths[pathNum++] = 0;
			qsort(paths, pathNum, sizeof(int), comp);
			outPaths();
		} else {
			n = -n;
			inPaths();
			outGraphs();
		}
	}
	return 0;
}

