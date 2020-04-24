#include<iostream>
#include<string>
#include<sstream>
#include<cmath>
using namespace std;

double M[15][35];
int E[15][35];

int main() {
	double a,b,c;
	int i,j,ai;
	for(i=0;i<10;++i)
		for(j=1;j<31;++j) {
			a = 1 - pow(2, -1-i);
			b = (1 << j) -1;
			c = log10(a) + b * log10(2);
			E[i][j] = floor(c);
			M[i][j] = pow(10, c-E[i][j]);
		}
	
	string s;
	while(cin >> s && s!="0e0") {
		for(i=0;i<s.size();++i)
			if(s[i] == 'e')
				s[i] = ' ';
		istringstream iss(s);
		iss >> a >> ai;
		while(a < 1) {
			a *= 10;
			--ai;
		}
		for(i=0;i<10;++i) {
			for(j=1;j<31;++j) {
				if(E[i][j] == ai && fabs(M[i][j]-a) < 1e-4) {
					cout << i << " " << j << endl;
				}
			}
		}
	}
	return 0;
}
