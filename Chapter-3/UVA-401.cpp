#include<cstdio>
#include<cstring>
#include<map>
using namespace std;

char s[25], s2[25];

bool palin(char * s) {
	int i, len = strlen(s);
	for(i=0; i<len/2; ++i)
		if(s[i] != s[len-i-1])
			return false;
	return true;
}

map<char,char> mp;

bool mirror(char * s) {
	int len = strlen(s);
	for(int i=0; i<=len/2; ++i)
		if(mp.find(s[i]) == mp.end() || mp[s[i]] != s[len-i-1])
			return false;
	return true;
}

void addmp() {
	mp['A'] = 'A';
	mp['E'] = '3';
	mp['H'] = 'H';
	mp['I'] = 'I';
	mp['J'] = 'L';
	mp['L'] = 'J';
	mp['M'] = 'M';
	mp['O'] = 'O';
	mp['S'] = '2';
	mp['T'] = 'T';
	mp['U'] = 'U';
	mp['V'] = 'V';
	mp['W'] = 'W';
	mp['X'] = 'X';
	mp['Y'] = 'Y';
	mp['Z'] = '5';
	mp['1'] = '1';
	mp['2'] = 'S';
	mp['3'] = 'E';
	mp['5'] = 'Z';
	mp['8'] = '8';

}

int main() {
	int i,j,k;
	bool mir, pal;
	addmp();
	while(scanf("%s", s) == 1) {
		strcpy(s2, s);
		pal = palin(s);
		mir = mirror(s);
		if(mir && pal)
			printf("%s -- is a mirrored palindrome.\n", s2);
		if(!mir && pal)
			printf("%s -- is a regular palindrome.\n", s2);
		if(mir && !pal)
			printf("%s -- is a mirrored string.\n", s2);
		if(!mir && !pal)
			printf("%s -- is not a palindrome.\n", s2);
		puts("");
	}
	return 0;
}
