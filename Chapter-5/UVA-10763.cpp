10391#include<stdio.h>
#include<vector>
#include<algorithm>

using namespace std;

int main() {
	int n, a, b, i, j, k;
	while(scanf("%d", &n) && n) {
		vector<int> lv, rv;
		for(i = 0; i < n; ++i) {
			scanf("%d %d", &a, &b);
			lv.push_back(a);
			rv.push_back(b);
		}
		sort(lv.begin(), lv.end());
		sort(rv.begin(), rv.end());
		for(i = 0; i < n; ++i) {
			if(lv[i] != rv[i]) {
				break;
			} 
		}
		if(i != n) {
			puts("NO");
		} else {
			puts("YES"); 
		}
	}
	return 0;
}
