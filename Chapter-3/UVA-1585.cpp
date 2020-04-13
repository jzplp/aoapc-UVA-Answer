#include<cstdio>
#include<cstring>
using namespace std;

char s[90];

int main() {
	int t,sum, i,j,a,c;
	scanf("%d", &t);
	while(t--) { 
		sum = 0;
		a = 0;
		scanf("%s", s);
		for(i=0; s[i]!=0; ++i) {
			if(s[i] == 'X') {
				a = 0;
			} else {
				++a;
				sum += a;
			}
		}
		printf("%d\n", sum);
	}
	return 0;
}
