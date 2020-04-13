#include<cstdio>
#include<cstring>
using namespace std;

char s[90];
int n;
bool judge(int a) {
	for(int i=0;i<n;++i) {
		if(s[i] != s[(a+i)%n])
			return false;
	}
	return true;
}

int main() {
	int i,a,t;
	scanf("%d", &t);
	while(t--) {
		scanf("%s", s);
		n = strlen(s);
		for(i=1;i<n;++i) {
			if(judge(i) == true)
				break;
		}
		printf("%d\n", i);
		if(t != 0)
			puts("");
	}
	return 0;
}
