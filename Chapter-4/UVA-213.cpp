#include<cstring>
#include<cstdio>

#define MAXN 10
#define MAXM 1000
char s[MAXM];
char arr[MAXN][MAXM];

bool getString() {
	char * p;
	while(1) {
		p = gets(s);
		if(p == NULL)
			return false;
		if(strlen(s) != 0)
			break;
	}
	int n = 1, len = strlen(s), i = 0, j;
	while(i < len) {
		for(j=0; j<((1<<n)-1); ++j) {
			arr[n][j] = s[i++];
			if(i >= len)
				break;
		}
		++n;
	}
	return true;
}

int func(int n) {
	int i = 0;
	char c;
	while(n > 0) {
		scanf("%c", &c);
		if(c != '0' && c != '1')
			continue;
		--n;
		i *= 2;
		if(c == '1')
			i += 1;
	}
	return i;
}

int main() {
	int len, a;
	while(getString()) {
		while(1) {
			len = func(3);
			if(len == 0)
				break;
			while(1) {
				a = func(len);
				if(a == (1<<len)-1)
					break;
				putchar(arr[len][a]);
			}
		}
		puts("");
	}
}
