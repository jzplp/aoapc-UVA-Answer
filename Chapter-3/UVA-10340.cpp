#include<string>
#include<iostream>
using namespace std;

string s1,s2;

bool findss(int a, int b) {
	if(a >= s1.size())
		return true;
	for(int i=b; i<s2.size(); ++i) {
		if(s1[a] != s2[i])
			continue;
		if(s1.size()-a > s2.size()-i)
			break;
		if(findss(a+1, i+1))
			return true;
	}
	return false;
}

int main() {
	int i,j,k;
	bool flag;
	while(cin >> s1 >> s2) {
		if(findss(0,0) == true)
			puts("Yes");
		else
			puts("No");
	}

	return 0;
}
