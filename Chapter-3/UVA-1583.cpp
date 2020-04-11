#include<cstdio>
using namespace std;

int arr[100005];

int countS(int a) {
	int c = 0;
	while(a > 0) {
		c += a%10;
		a /= 10;
	}
	return c;
}

int main() {
	int n,i,a;
	for(i=0; i<100000; ++i) {
		a = i + countS(i);
		if(a <= 100000 && arr[a] == 0)
			arr[a] = i;
	}
	scanf("%d", &n);
	while(n--) {
		scanf("%d", &a);
		printf("%d\n", arr[a]);
	}
	return 0;
}
