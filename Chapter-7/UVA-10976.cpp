#include<stdio.h>
#include<string>
using namespace std;
 
int k;
string s;
char line[1000];
 
int computed() {
	int i, x, y;
	int count = 0;
	s = "";
	for(y = k + 1; y <= 2*k; ++y) {
		x = (k * y) / (y - k);
		if(x * (y - k) == k * y) {
			sprintf(line, "1/%d = 1/%d + 1/%d\n", k, x, y);
			s = s + line;
			++count;
		}
	}
	return count;
}
 
int main() {
	while(scanf("%d", &k) == 1) {
		printf("%d\n", computed());
		printf(s.c_str());
	}
	return 0;
} 
