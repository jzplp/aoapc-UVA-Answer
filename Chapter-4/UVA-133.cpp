#include<cstring>
#include<cstdio>

#define MAXN 22
bool arr[MAXN];

int main() {
	int t,i,j,lent;
	int n,k,m;
	int xt,yt;
	while(scanf("%d %d %d", &n,&k,&m) == 3 && n != 0) {
		for(i=0; i!=n; ++i)
			arr[i] = false;
		lent = n;
		xt = 0, yt = n-1;
		while(lent > 0) {
			for(i=0; i!=k; ++i) {
				while(arr[xt] == true)
					xt = (xt+1)%n;
				if(i != k-1)
					xt = (xt+1)%n;
			}
			for(i=0; i!=m; ++i) {
				while(arr[yt] == true) {
					--yt;
					if(yt < 0)
						yt = n-1;
				}
				if(i != m-1) {
					--yt;
					if(yt < 0)
						yt = n-1;
				}
			}
			if(xt == yt) {
				printf("%3d", xt+1);
				--lent;
			} else {
				printf("%3d%3d", xt+1,yt+1);
				lent-=2;
			}
			arr[xt] = true;
			arr[yt] = true;
			if(lent != 0)
				putchar(',');
		}
		puts("");
	}
	return 0;
}
