#include<stdio.h>
#include<stdlib.h>
int arr[1000];
int m,n, water;

double level;

int cmp(const void *i , const void *j) {
	return *(int *)i - *(int *)j;
}

double culLevel(int i) {
	return (double)water / (i * 100) + level;
}

int cul() {
	int levelt = arr[0];
	level = levelt;
	if(water <= 0) {
		return 0;
	}
	int i;
	for(i = 1; i < m * n; ++i) {
		if(arr[i] == levelt) {
			continue;
		}
		if(water == i * (arr[i] - levelt) * 100) {
			levelt = arr[i];
			level = levelt;
			return i;
		} else if(water > i * (arr[i] - levelt) * 100) {
			water -= i * (arr[i] - levelt) * 100;
			levelt = arr[i];
			level = levelt;
		} else {
			level = culLevel(i);
			return i;
		}
	}
	level = culLevel(m * n); 
	return m * n;
}


int main() {
	int count = 0;
	int i, j, k;
	int region;
	while(scanf("%d %d", &m ,&n) == 2 && m != 0) {
		for(i = 0; i < m; ++i) {
			for(j = 0; j < n; ++j) {
				scanf("%d", &arr[i*n + j]);
			}
		}
		scanf("%d", &water);
		qsort(arr, m*n, sizeof(int), cmp);
	
		region = cul();
		
		// if(count != 0) { putchar('\n'); }
		printf("Region %d\n", ++count);
		printf("Water level is %.2lf meters.\n", level);
		printf("%.2lf percent of the region is under water.\n", 100 * (double)region/(m*n));
		putchar('\n');
	}
	return 0; 
} 