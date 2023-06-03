#include<stdio.h>
#include<string.h>
#include<queue>

using namespace std; 

int board[100];
int begg, endd;
int step1[8] = {1, 2,  2,  1, -1, -2, -2, -1};
int step2[8] = {2, 1, -1, -2, -2, -1,  1,  2};

int word2value(char *s) {
	int x = s[0] - 'a' + 1;
	int y = s[1] - '0';
	return x * 10 + y;
}

int countValue(int a, int i) {
	int x = a / 10;
	int y = a % 10;
	x += step1[i];
	y += step2[i];
	if(x < 1 || x > 8 || y < 1 || y > 8) {
		return -1;
	}
	return x * 10 + y;
}

int move() {
	int num = 0, level = begg,levelt, pa, a, b, i;
	queue<int> qu;
	qu.push(begg);
	while(qu.size()) {
		pa = qu.front();
		qu.pop();
		// printf("%d %d %d\n", num, pa, level);
		if(pa == endd) {
			return num;
		}
		if(level == pa) {
			++num;
			level = -1; 
		}
		for(i = 0; i < 8; ++i) {
			a = countValue(pa, i);
			if(a < 0) continue;
			if(board[a]) continue;
			levelt = a;
			board[a] = 1;
			qu.push(a);
		}
		if(level == -1) level = levelt;
	}
	return -1;
}

int main() {
	char word1[5], word2[5];
	int num;
	while(scanf("%s %s", word1, word2) == 2) {
		begg = word2value(word1);
		endd = word2value(word2);
		// printf("%d %d \n", begg, endd);
		memset(board, 0, sizeof(board));
		num = move();
		printf("To get from %s to %s takes %d knight moves.\n", word1, word2, num);
	}
	return 0;
}

