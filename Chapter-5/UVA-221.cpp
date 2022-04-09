#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct building {
	int id;
	double x, y, w, d, h;
	bool operator < (const building &rhs) {
		if(x != rhs.x) {
			return x < rhs.x; 
		}
		return y < rhs.y; 
	}
};


bool judge(vector<building> &v, int a, double x) {
	int i, j;
	for(i = 0; i < v.size(); ++i) {
		if(i == a) {
			continue;
		}
		if(x > (v[i].x + v[i].w) || x < v[i].x) {
			continue;
		}
		if(v[i].y >= v[a].y) continue;
		if(v[i].h >= v[a].h) return false;
	}
	return true;
}

int main() {
	int k = 0, n;
	int i, j;
	bool flag;
	while(cin >> n && n != 0) {
		vector<building> v;
		vector<int> vx;
		
		for(i = 0; i < n; ++i) {
			building b;
			cin >> b.x >> b.y >> b.w >> b.d >> b.h;
			b.id = i + 1;
			v.push_back(b);
			vx.push_back(b.x);
			vx.push_back(b.x + b.w);
		}
		
		sort(v.begin(), v.end());
		sort(vx.begin(), vx.end());
		int m = unique(vx.begin(), vx.end()) - vx.begin();
		/*
		for(i = 0; i < n; ++i) {
			cout << v[i].x << " " <<  v[i].y << " " <<  v[i].w << " " <<  v[i].d << " " <<  v[i].h << endl;
		} 
		for(i = 0; i < m; ++i) {
			cout << vx[i] << " ";
		}
		cout <<endl;
		*/
		
		if(k != 0) {
			cout << endl;
		}
		++k;
		cout << "For map #" << k << ", the visible buildings are numbered as follows:" << endl;
		cout << v[0].id;
		
		for(i = 1; i < n; ++i) {
			flag = false;
			for(j = 1; j < m; ++j) {
				double halfx = (vx[j] + vx[j-1]) / 2;
				if(halfx > (v[i].x + v[i].w) || halfx < v[i].x) {
					continue;
				}
				if(judge(v, i, halfx)) {
					flag = true;
					break;
				} 
			}
			if(flag) {
				cout << " " << v[i].id;
			}
		}
		cout << endl;
	}
	return 0;
}
