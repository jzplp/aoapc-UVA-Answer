#include<iostream>
#include<string>
#include<set>
#include<algorithm>
using namespace std;

int main() {
	int i,j,k,c;
	bool flag=false;
	while((c=getchar()) != EOF) {
		if(c=='"') {
			if(flag)
				printf("''");
			else
				printf("``");
			flag = !flag;
		}
		else
			putchar(c);
	}
	return 0;
}
