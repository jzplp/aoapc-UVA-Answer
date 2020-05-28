#include<cstdio>

int arr[10][10] = {
	{0},
	{5,4,2,3,6},
	{1,4,6,3,5},
	{5,1,2,6,4},
	{1,5,6,2,3},
	{6,4,1,3,2},
	{2,4,5,3,1}
};

char s1[10],s2[10];

bool judge(int a) {
	int i,j,k;
	for(i=0; i<4; ++i) {
		for(j=0; j<4; ++j)
			if(s1[arr[1][j]] != s2[arr[a][(j+i)%4]])
				break;
		if(j == 4 && s1[arr[1][4]] == s2[arr[a][4]])
			return true;
	}
	return false;
}

int main() {
	int i,j;
	while(scanf(" %c",&s1[1]) == 1) {
		for(i=2; i<7; ++i)
			scanf(" %c", &s1[i]);
		for(i=1; i<7; ++i)
			scanf(" %c", &s2[i]);
		for(i=1; i<7; ++i)
			if(s1[1] == s2[i])
				if(judge(i))
					break;
		if(i == 7)
			puts("FALSE");
		else
			puts("TRUE");
	}
	return 0;
}
