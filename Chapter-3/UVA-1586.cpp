#include<cstdio>
#include<cstring>
#include<map>
using namespace std;

char s[90]; 
map<char, double> mp;

int main() {
	int t, a,i,j,k;
	double sum;
	char c; 
	mp['C'] = 12.01;
	mp['H'] = 1.008;
	mp['O'] = 16.0;
	mp['N'] = 14.01;
	
	scanf("%d", &t);
	while(t--) {
		scanf("%s", s);
		sum = 0;
		i = 0;
		while(s[i] != 0) {
			c = s[i];
			a = 0;
			while(isdigit(s[++i]))
				a = a * 10 + s[i] - '0';
			if(a == 0)
				sum += mp[c];
			else
				sum += mp[c] * a;
		}
		printf("%.3lf\n", sum);
	}
	
	return 0;
}
