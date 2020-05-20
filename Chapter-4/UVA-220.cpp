#include<cstdio>

#define MAXN 10
char arr[MAXN][MAXN];
char player;
char x,y;

void changeBW() {
	if(player == 'B')
		player = 'W';
	else
		player = 'B';
}

void showBoard() {
	int i,j;
	for(i=1; i<9; ++i) {
		for(j=1; j<9; ++j)
			putchar(arr[i][j]);
		putchar('\n');
	}
}

int xstep[8] = {1,0,-1,0,1,-1,-1,1};
int ystep[8] = {0,1,0,-1,1,-1,1,-1};

bool move() {
	int i,j,k;
	int xt,yt;
	bool flagMove = false ,flag;
	for(i=0; i<8; ++i) {
		xt = x + xstep[i];
		yt = y + ystep[i];
		if(xt < 1 || xt > 8 || yt < 1 || yt > 8)
			continue;
		if(arr[xt][yt] == '-' || arr[xt][yt] == player)
			continue;
		flag = false;
		while(1) {
			xt = xt + xstep[i];
			yt = yt + ystep[i];
			if(xt < 1 || xt > 8 || yt < 1 || yt > 8 || arr[xt][yt] == '-')
				break;
			if(arr[xt][yt] == player) {
				flag = true;
				break;
			}
		}
		if(flag == false)
			continue;
		flagMove = true;
		arr[x][y] = player;
		for( ; !(xt==x&&yt==y); xt = xt - xstep[i],yt = yt - ystep[i])
			arr[xt][yt] = player;
	}
	return flagMove;
}

void showList() {
	int i,j,k,xt,yt;
	bool flagMove = false, flag;
	for(i=1;i<9;++i) 
		for(j=1;j<9;++j) {
			if(arr[i][j] != '-')
				continue;
			for(k=0;k<8;++k) {
				xt = i + xstep[k];
				yt = j + ystep[k];
				if(xt < 1 || xt > 8 || yt < 1 || yt > 8)
					continue;
				if(arr[xt][yt] == '-' || arr[xt][yt] == player)
					continue;
				flag = false;
				while(1) {
					xt = xt + xstep[k];
					yt = yt + ystep[k];
					if(xt < 1 || xt > 8 || yt < 1 || yt > 8 || arr[xt][yt] == '-')
						break;
					if(arr[xt][yt] == player) {
						flag = true;
						break;
					}
				}
				if(flag == false)
					continue;
				if(flagMove == true)
					putchar(' ');
				flagMove = true;
				printf("(%d,%d)",i,j);
				break;
			}
		}
	if(flagMove == false)
		puts("No legal move.");
	else
		puts("");
}

void stat() {
	int b=0,w=0,i,j;
	for(i=1;i<9;++i)
		for(j=1;j<9;++j) {
			if(arr[i][j] == 'B')
				++b;
			if(arr[i][j] == 'W')
				++w;
			}
	printf("Black - %2d White - %2d\n", b,w);
}

void choose() {
	char c;
	while(1) {
		scanf(" %c", &c);
		switch(c) {
			case 'L':
				showList();
				break;
			case 'M':
				scanf(" %c%c",&x,&y);
				x -= '0';
				y -= '0';
				if(move() == false) {
					changeBW();
					move();
				}
				changeBW();
				stat();
				break;
			case 'Q':
				showBoard();
				return;
		}
	}
}

int main() {
	int n,i,j,k;
	char c;
	scanf("%d", &n);
	for(k=0; k<n; ++k) {
		if(k != 0)
			puts("");
		for(i=1; i<9; ++i)
			for(j=1; j<9; ++j)
				scanf(" %c", &arr[i][j]);
		scanf(" %c", &player);
		choose();
	}
	return 0;
}
