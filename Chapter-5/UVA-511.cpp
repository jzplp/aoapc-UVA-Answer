#include<iostream>
#include<map>
#include<string>
#include<algorithm>
#include<vector>

using namespace std;

struct LOC {
	double x, y;	
}; 

struct MAP {
	double x1, x2, y1, y2;
	double cenx, ceny;
	double radio;
	double area;
	string name;
};

vector<MAP> vm;
map<string, vector<int>> mp; 
double xt, yt;

double compDis(MAP &m, int x, int y) {
	return (m.cenx - x) * (m.cenx - x) + (m.ceny - y) * (m.ceny - y);
}

double compDisRC(MAP &m, int x, int y) {
	return (m.x2 - x) * (m.x2 - x) + (m.y2 - y) * (m.y2 - y);
}

bool cmp(int l, int r) {
	MAP &m1 = vm[l], &m2 = vm[r];
	if(m1.area != m2.area) {
		return m1.area > m2.area;
	}
	double dis1 = compDis(m1, xt ,yt), dis2 = compDis(m2, xt ,yt);
	if(dis1 != dis2) {
		return dis1 < dis2;
	}
	if(m1.radio != m2.radio) {
		return m1.radio < m2.radio;
	}
	dis1 = compDisRC(m1, xt ,yt);
	dis2 = compDisRC(m2, xt ,yt);
	if(dis1 != dis2) {
		return dis1 > dis2;
	}
	return m1.x1 < m2.x1;
}

int main() {
	string line, word;
	double x1, x2, y1, y2;
	int i, j, t;
	getline(cin ,line);
	while(cin >> word && word != "LOCATIONS") {
		MAP m;
		m.name = word;
		cin >> x1 >> y1 >> x2 >> y2;
		if(x1 > x2) {
			m.x1 = x2;
			m.x2 = x1;
		} else {
			m.x2 = x2;
			m.x1 = x1;
		}
		if(y1 > y2) {
			m.y1 = y2;
			m.y2 = y1;
		} else {
			m.y2 = y2;
			m.y1 = y1;
		}
		m.cenx = (m.x1 + m.x2) / 2;
		m.ceny = (m.y1 + m.y2) / 2;
		m.radio = (m.x2 - m.x1) / (m.y2 - m.y1);
		m.radio = m.radio - 0.75;
		if(m.radio < 0) {
			m.radio = -m.radio;
		}
		m.area = (m.x2 - m.x1) * (m.y2 - m.y1);
		vm.push_back(m);
	}
	
	while(cin >> word && word != "REQUESTS") {
		cin >> xt >> yt;
		vector<int> v;
		for(i = 0; i < vm.size(); ++i) {
			if(vm[i].x1 <= xt && vm[i].x2 >= xt && vm[i].y1 <= yt && vm[i].y2 >= yt) {
				v.push_back(i);
			}
		}
		sort(v.begin(), v.end(), cmp);
		vector<int> vt;
		for(i = 0; i < v.size(); ++i) {
			if(i == 0) {
				vt.push_back(v[0]);
				continue;
			}
			if(vm[vt[vt.size() - 1]].area == vm[v[i]].area) {
				continue;
			}
			vt.push_back(v[i]);
		}
		mp[word] = vt;
	}
	
	while(cin >> word && word != "END") {
		cin >> t;
		cout << word << " at detail level " << t << ' ';
		if(!mp.count(word)) {
			cout << "unknown location";
		} else if(mp[word].size() == 0) {
			cout << "no map contains that location";
		} else if(mp[word].size() >= t) {
			cout << "using " << vm[mp[word][t-1]].name;
		} else {
			cout << "no map at that detail level; using " << vm[mp[word][mp[word].size() - 1]].name;
		}
		cout << endl; 
	}
		
	return 0;
}

