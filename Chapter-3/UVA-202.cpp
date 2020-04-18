#include<cstdio>

#define MAXN 1000000
int arr[MAXN];
int chu[MAXN];

int main() {
	int a,b,m,n,i,j,k;
	int cyc;
	bool flag;
	while(scanf("%d %d", &a, &b) == 2) {
		if(b == 0)
			continue;
		m = a, n = b;
		i = -1;
		flag = false;
		a %= b;
		a *=10;
		while(i < MAXN) {
			if(a == 0)
			{
				++i;
				arr[i] = 0;
				arr[i+1] = 0;
				chu[i] = 0;
				chu[i+1] = 0;
				++i;
				cyc = 1;
				break;
			}
			for(j=0;j<i;++j) {
				if(chu[i] == chu[j] && arr[i] == arr[j])
				{
					cyc = i-j;
					flag = true;
					break;
				}
			}
			if(flag == true)
				break;
			++i;
			arr[i] = a/b;
			a %= b;
			chu[i] = a;
			if(a < b) {
				a *= 10;
			}
		}
		printf("%d/%d = %d.", m, n, m/n);
		for(j=0;j<(i-cyc);++j) 
			printf("%d",arr[j]);
		putchar('(');
		for(j=0;j<cyc && j<50;++j)
			printf("%d",arr[j+i-cyc]);
		if(cyc > 50)
			printf("...");
		puts(")");
		/*
		for(j=0;j<=i;++j)
			printf("[%d %d]",arr[j], chu[j]);
		puts("");
		*/
		printf("   %d = number of digits in repeating cycle\n\n", cyc);
	}

	return 0;
}
