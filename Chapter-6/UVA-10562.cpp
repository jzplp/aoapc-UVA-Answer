#include<stdio.h>
#include<string.h>

#define MAXN 210

char treestr[MAXN][MAXN];
char str[MAXN];
int num;

void clear() {
	memset(treestr, 0, sizeof(treestr));
}

bool input() {
	num = 0;
	while(fgets(treestr[num], MAXN, stdin) != NULL) {
		if(treestr[num][0] == '#') {
			return true;
		}
		++num;
	}
	return false; 
}

bool isNode(char c) {
	switch(c) {
		case ' ':
		case '-':
		case '|':
		case '\n':
		case '#':
		case '\0':
			return false;
	}
	return true;
}

void dfs(int a, int b) {
	int beg, end, i;
	printf("%c", treestr[a][b]);
	putchar('(');
	if(treestr[a+1][b] == '|') {
		for(i = b; treestr[a+2][i] == '-'; --i) ;
			beg = i+1;
		for(i = b; treestr[a+2][i] == '-'; ++i) ;
			end = i;
		for(i = beg; i != end; ++i) {
			if(isNode(treestr[a+3][i])) {
				dfs(a+3, i);
			}
		}
	}
	putchar(')');
}

void handle() {
	int i = 0, j;
	putchar('(');
	for(j = 0; j < MAXN; ++j) {
		if(isNode(treestr[0][j])) {
			dfs(0, j);
			break;	
		}
	}
	putchar(')');
}

int main() {
	int T;
	scanf("%d", &T); 
	fgets(str, MAXN, stdin);
	while(1) {
		clear();
		if(!input()) {
			break;
		}
		handle();
		putchar('\n');
	}
	return 0;
}
