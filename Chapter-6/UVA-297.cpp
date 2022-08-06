#include<stdio.h>
#include<string.h>

int cnt, p;
char str[2050];
int box[33][33];

void count(int r, int c, int w) {
	char ch = str[p++];
	if(ch == 'f') {
		int i, j;
		for(i = 0; i < w; ++i) {
			for(j = 0; j < w; ++j) {
				if(!box[r + i][c + j]) {
					box[r + i][c + j] = 1;
					++cnt;
				}
			}
		}
	}
	if(ch == 'p') {
		count(r, c + w/2, w/2);
		count(r, c, w/2);
		count(r + w/2, c, w/2);
		count(r + w/2, c + w/2, w/2);
	}
}

int main() {
	int n;
	scanf("%d", &n);
	while(n--) {
		cnt = 0;
		p = 0;
		memset(box, 0, sizeof(box));
		scanf("%s", str);
		count(0, 0, 32);
		p = 0;
		scanf("%s", str);
		count(0, 0, 32);
		printf("There are %d black pixels.\n", cnt);
	}
	return 0;
}
