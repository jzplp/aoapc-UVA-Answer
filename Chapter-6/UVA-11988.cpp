#include<cstdio>
#include<cstring>

using namespace std;

char sin[100005];
int next[100005];
int begin, end, pos;

int main() {
	int i, j, n;
	while(scanf("%s", sin+1) == 1) {
		next[0] = 0;
		pos = 0;
		end = 0;
		n = strlen(sin+1);
		for(i = 1; i <= n; ++i) {
			if(sin[i] == '[') {
				pos = 0;
				continue;
			}
			if(sin[i] == ']') {
				pos = end;
				continue;
			}
			next[i] = next[pos];
			if(pos == end) {
				end = i;
			}
			next[pos] = i;
			pos = i;
		}
		for(i = next[0]; i != 0; i = next[i]) {
			putchar(sin[i]);
		}
		putchar('\n');
	}
	return 0;
}
