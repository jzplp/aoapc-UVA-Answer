#include<stdio.h>
#include<algorithm>
#include<vector>

using namespace std;

int main() {
	vector<int> v1;
	int c = 0;
	int n, q, i, j, k;
	while(scanf("%d%d", &n, &q) == 2 && n > 0) {
		printf("CASE# %d:\n", ++c);
		v1.clear();
		for(i = 0; i < n; ++i) {
			scanf("%d", &j);
			v1.push_back(j);
		}
		sort(v1.begin(), v1.end());
		while(q--) {
			scanf("%d", &j);
			auto ip = lower_bound(v1.begin(), v1.end(), j);
			if(*ip == j) {
				printf("%d found at %d\n", j, ip - v1.begin() + 1);
			} else {
				printf("%d not found\n", j);
			}
		}
	}
	return 0;
}
