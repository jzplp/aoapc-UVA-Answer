#include<cstdio>
#include<cstring>
using namespace std;

#define MAXN 210
char s[MAXN];

int main() {
	int n,i,j,k,a;
	scanf("%d", &n);
	while(n--) {
		scanf("%s", s);
		a = strlen(s);
		for(i=a;i<=a*2;++i)
			s[i] = s[i-a];
		j = 0;
		for(i=1;i<=a;++i)
			j = strncmp(s+j, s+i, a) >= 0 ? i : j;
		for(i=0;i<a;++i)
			putchar(s[i+j]);
		puts("");
	}
	return 0;
}
