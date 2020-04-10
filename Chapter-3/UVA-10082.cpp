#include<iostream>
#include<cstring>
#include<set>
#include<algorithm>
using namespace std;

char s[100] = "`1234567890-=\tQWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./";

int main() {
	int c;
	char * p;
	while((c=getchar()) != EOF)
	{
		p = strchr(s, c);
		if(p == NULL)
			putchar(c);
		else 
			putchar(*--p);
	}
	return 0;
}
