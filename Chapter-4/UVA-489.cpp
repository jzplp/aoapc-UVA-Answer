#include<cstring>
#include<cstdio>


#define MAXN 10010
char s[MAXN], st[MAXN];
bool vis[MAXN];

int main() {
	int t,i,j,k,len;
	char c;
	bool flagFin, flagO;
	while(scanf("%d", &t) == 1 && t!=-1) {
		scanf("%s", s);
		scanf("%s", st);
		len = strlen(s);
		for(i=0; i<len; ++i)
			vis[i] = false;
		k = 0;
		for(i=0; st[i]!=0; ++i) {
			flagFin = true;
			flagO = false;
			for(j=0; j<len; ++j) {
				if(vis[j] == true)
					continue;
				flagFin=false;
				if(st[i] == s[j]) {
					vis[j] = true;
					flagO = true;
				}
			}
			if(flagFin == true)
				break;
			if(flagO == false)
				++k;
		}
		for(i=0; i<len; ++i)
			if(vis[i] == false)
				break;
		printf("Round %d\n", t);
		if(k > 6)
			puts("You lose.");
		else if(flagFin == true || i == len)
			puts("You win.");
		else
			puts("You chickened out.");
	}
	return 0;
}
