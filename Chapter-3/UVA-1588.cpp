#include<cstdio>
#include<cstring>

#define MAXN 205
char s1[MAXN];
char s2[MAXN];

int main() {
	int i,j,k,n, len1, len2;
	int a1, a2;
	while(scanf("%s %s", s1, s2) == 2) {
		len1 = strlen(s1);
		len2 = strlen(s2);
		for(i=0; i<len1; ++i) {
			j = 0;
			k = i;
			while(j < len2) {
				if(k < len1 && (int)s1[k]-'0' + s2[j]-'0' > 3)
					break;
				++j;
				++k;
			}
			if(j == len2)
				break;
		}
		a1 = i+len2 > len1 ? i+len2 : len1;
		for(i=0; i<len2; ++i) {
			j = 0;
			k = i;
			while(j < len1) {
				if(k < len2 && (int)s2[k]-'0' + s1[j]-'0' > 3)
					break;
				++j;
				++k;
			}
			if(j == len1)
				break;
		}
		a2 = i+len1 > len2 ? i+len1 : len2;
		printf("%d\n", a1<a2?a1:a2);
	}
	return 0;
}
