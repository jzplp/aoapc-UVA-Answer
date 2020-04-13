#include<cstdio>
#include<cstring>
#include<map>
using namespace std;

char s[6][6];
char arr[10];
map<char, int> mp;
int addx[4] = {-1,1,0,0};
int addy[4] = {0,0,-1,1};
int ix, iy;

bool moving(int a) {
	int tx=ix+addx[a];
	int ty=iy+addy[a];
	if(tx < 1 || tx > 5 || ty < 1 || ty > 5)
		return false;
	swap(s[ix][iy], s[tx][ty]);
	ix = tx;
	iy = ty;
	return true;
}

int main() {
	int t,i,j,k,a;
	bool flag;
	mp['A'] = 0;
	mp['B'] = 1;
	mp['L'] = 2;
	mp['R'] = 3;
	t=0;
	while(1) {
		for(i=1; i<=5; ++i) {
			for(j=1; j<=5; ++j) {
				scanf("%c", &s[i][j]);
				if(s[i][j] == 'Z')
					return 0;
				if(s[i][j] == ' ') {
					ix = i;
					iy = j;
				}
			}
			fgets(arr, 10, stdin);
		}
		if(t != 0)
			puts("");
		flag = true;
		while(scanf("%s", arr) == 1) {
			for(i=0; arr[i] != 0; ++i) {
				if(arr[i] == '0')
					continue;
				if(flag == true && moving(mp[arr[i]]) == false)
					flag = false;
			}
			if(arr[i-1] == '0')
				break;
		}
		fgets(arr, 10, stdin);
		printf("Puzzle #%d:\n", ++t);
		if(flag == false) {
			puts("This puzzle has no final configuration.");
			continue;
		}
		for(i=1; i<=5; ++i) {
			for(j=1; j<=5; ++j) {  
				printf("%c", s[i][j]);
				if(j == 5) 
					puts("");
				else
					putchar(' ');
			}
		}
	}
	return 0;
}
