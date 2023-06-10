#include<stdio.h>
#include<string.h>
#include<math.h>
#include<map>

using namespace std;
char line[400000];
int nodeNum;

int getNum(long long * v, int i) {
	long long sum = 0;
	for(; line[i] >= '0' && line[i]<= '9'; ++i) {
		sum = sum * 10 + line[i] - '0';
	}
	*v = sum;
	return i - 1;
}

int createTree(int i, int level, map<long long, int> &mp) {
	long long v, k;
	if(line[i] == '[') {
		 i = createTree(i + 1, level + 1, mp);
		 i = createTree(i + 2, level + 1, mp);
		 i = i + 1;
	} else {
		i = getNum(&v, i);
		k = v << (level - 1);
		mp[k] = mp[k] + 1;
		++nodeNum;
	}
	return i;
}

int main() {
	int n, i, j, k, maxNum;
	scanf("%d", &n);
	while(n--) {
		scanf("%s", line);
		map<long long, int> mp;
		nodeNum = 0;
		createTree(0, 1, mp);
		maxNum = 0;
		for(auto ip = mp.begin(); ip != mp.end(); ++ip) {
			maxNum = max(maxNum, ip->second);
			// printf("%d %d\n", ip->first, ip->second);
		}
		printf("%d\n", nodeNum - maxNum);
	}
	return 0;
}
