#include<cstdio>

#define MAXM 55
#define MAXN 1010
char arr[MAXM][MAXN];
char num[MAXM];
char s[5] = "ACGT";

int main() {
	int t,m,n,i,j,k;
	int ct, con, sum;
	char c;
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d", &m, &n);
		for(i=0;i!=m;++i) {
			scanf("%s", arr[i]);
		}
		sum = 0;
		for(i=0;i!=n;++i)
		{
			con = n;
			c = 'A';
			for(j=0;j<4;++j) {
				ct = m;
				for(k=0;k<m;++k)
					if(s[j] == arr[k][i])
						--ct;
				if(con > ct) {
					con = ct;
					c = s[j];
				}
			}
			num[i] = c;
			sum += con;
		}
		num[n] = 0;
		printf("%s\n%d\n", num, sum);
	}
	
	return 0;
}
