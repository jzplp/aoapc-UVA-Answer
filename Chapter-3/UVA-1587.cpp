#include<cstdio>
#include<iostream>
#include<map>
using namespace std;

struct point {
	int x, y;
	bool operator=(const point & rhs) const{
		if(x == rhs.x && y == rhs.y)
			return true;
		return false;
	}
	bool operator<(const point & rhs) const {
		if(x == rhs.x)
			return y < rhs.y;
		return x < rhs.x;
	}
};


int main() {
	int i,j,k,n,m;
	point po;
	bool flag;
	while(scanf("%d %d",&po.x, &po.y) == 2) {
		map<point, int> mp;
		map<int, int> mp2; 
		if(po.x > po.y)
			swap(po.x, po.y);
		mp[po]++;
		mp2[po.x]++;
		mp2[po.y]++; 
		for(i=0;i<5;++i) {
			scanf("%d %d", &po.x, &po.y);
			if(po.x > po.y)
				swap(po.x, po.y);
			mp2[po.x]++;
			mp2[po.y]++; 
			mp[po]++; 
		}
		flag = true;
		for(auto pi = mp.begin(); pi != mp.end(); ++pi) {
			//printf("%d %d %d\n", pi->first.x, pi->first.y, pi->second);
			if(pi->second % 2 != 0) {
				flag = false;
				break;
			}
		}
		for(auto pi = mp2.begin(); pi != mp2.end(); ++pi) {
			//printf("[%d %d] ", pi->first, pi->second);
			if(pi->second % 4 != 0) {
				flag = false;
				break;
			}
		}
		if(flag)
			puts("POSSIBLE");
		else
			puts("IMPOSSIBLE");
	}
	return 0;
}
