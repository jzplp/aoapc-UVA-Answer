#include<stdio.h>

#define MAXN 100005
int left[MAXN];
int right[MAXN];

int inv, n, m;

void init() {
	int i;
	inv = 0;
	for(i = 0; i <= n; ++i) { 
		left[i] = (i + n) % (n + 1);
		right[i] = (i + 1) % (n + 1);
	}
}

void swap(int x, int y) {
	int xl = left[x], xr = right[x];
	int yl = left[y], yr = right[y];
	
	if(right[x] != y && right[y] != x) {
		right[xl] = y;
		left[y] = xl;
		
		left[xr] = y;
		right[y] = xr;
		
		right[yl] = x;
		left[x] = yl;
		
		left[yr] = x;
		right[x] = yr;
		return;
	}
	
	if(right[x] == y) {
		right[xl] = y;
		left[y] = xl;
		
		left[yr] = x;
		right[x] = yr;
		
		left[x] = y;
		right[y] = x;
		return;
	}
	
	if(right[y] == x) {
		right[yl] = x;
		left[x] = yl;
		
		left[xr] = y;
		right[y] = xr;
		
		left[y] = x;
		right[x] = y;
		return;
	}
}

void change1(int x, int y) {
	if(right[x] == y) {
		return;
	}
	int xl = left[x], xr = right[x];
	int yl = left[y], yr = right[y];
	
	right[xl] = xr;
	left[xr] = xl;
	
	right[yl] = x;
	left[x] = yl;
	
	left[y] = x;
	right[x] = y;
}

void change2(int x, int y) {
	if(left[x] == y) {
		return;
	}
	int xl = left[x], xr = right[x];
	int yl = left[y], yr = right[y];
	
	right[xl] = xr;
	left[xr] = xl;
	
	left[yr] = x;
	right[x] = yr;
	
	right[y] = x;
	left[x] = y;
}

long long count() {
	int i;
	int type, x, y;
	for(i = 0; i < m; ++i) {
		scanf("%d", &type);
		if(type < 4) {
			scanf("%d %d", &x, &y);
		} else {
			inv = 1 - inv;
			continue;
		}
		if(type == 3) {
			swap(x, y);
			continue;
		}
		if(inv) {
			type = 3 - type;
		}
		if(type == 1) {
			change1(x, y);
			continue;
		}
		if(type == 2) {
			change2(x, y);
			continue;
		}
	}
	
	x = 0;
	long long sum = 0;
	for(i = 1; i <= n; ++i) {
		x = right[x];
		if(i % 2 == 1)
			sum += x;
	}
	if(inv && n % 2 == 0) {
		sum = n * (long long)(n + 1) / 2 - sum;
	}
	return sum;
}


int main() {
	int i = 0;
	long long sum = 0;
	while(scanf("%d %d", &n, &m) == 2) {
		++i;
		init();
		sum = count();
		printf("Case %d: %lld\n", i, sum);
	}
	return 0;
}
