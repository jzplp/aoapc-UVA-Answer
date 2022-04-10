#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct point {
	int x, y;
};

bool cmp1(const point &lhs, const point &rhs) {
	if(lhs.x != rhs.x) {
		return lhs.x < rhs.x;
	}
	return lhs.y < rhs.y;
} 

bool cmp2(const point &lhs, const point &rhs) {
	if(lhs.x != rhs.x) {
		return lhs.x < rhs.x;
	}
	return lhs.y > rhs.y;
} 

int main() {
	int t, n, i, j, k, a, b;
	cin >> t;
	bool cut2, flag; 
	while(t--) {
		vector<point> v;
		cin >> n;
		for(i = 0; i < n; ++i) {
			point p;
			cin >> p.x >> p.y;
			v.push_back(p);
		}
		sort(v.begin(), v.end(), cmp1);
		int beg1 = 0, end1, beg2, end2 = n - 1, xcut;
		cut2 = false;
		if(n % 2 == 0) {
			end1 = n/2 - 1;
			beg2 = n/2;
			int sum = v[beg2].x + v[end1].x;
			xcut = sum / 2;
			if(sum % 2 != 0) {
				cut2 = true;
			}
			// xcut = (v[n/2].x + v[n/2 - 1].x) / 2;
		} else {
			xcut = v[n/2].x;
			end1 = n/2 - 1;
			beg2 = n/2 + 1;
		}
		sort(v.begin() + beg2, v.end(), cmp2);
		flag = true;
		for(i = beg1; i <= end1; ++i) {
			a = i;
			b = end2 - i;
			if(v[a].x == xcut && v[b].x == xcut) {
				continue;
			}
			if(v[a].y != v[b].y) {
				flag = false;
				break;
			}
			if(!cut2) {
				if((xcut - v[a].x) != (v[b].x - xcut)) {
					flag = false;
					break;
				}
			}
			if(cut2) {
				if((xcut - v[a].x) != (v[b].x - xcut - 1)) {
					flag = false;
					break;
				}
			}
		}
		if(flag) {
			cout << "YES" << endl;
		} else {
			cout << "NO" << endl;
		}
	}
	return 0;
}
