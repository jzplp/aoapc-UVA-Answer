#include<cstdio>
#include<cstring>
using namespace std;

int arr[12];

void addnum(int n) {
	while(n>0) {
		arr[n%10]++;
		n/=10; 
	} 
}

int main() {
	int i,j,k,a,t,n;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(i=0; i<10; ++i)
			arr[i] = 0;
		for(i=1; i<=n; ++i)
			addnum(i);
		for(i=0; i<10; ++i) {
			printf("%d", arr[i]);
			if(i!=9)
				putchar(' ');
		}
		puts("");
	}
	return 0;
}
