#include<iostream>
#include<map>
#include<vector>
#include<queue>
#include<string>

using namespace std;

int main() {
	int t, n = 0, a, b, i, j;
	string s; 
	while(cin >> t && t != 0) {
		cout << "Scenario #" << ++n << endl;
		map<int, int> mp;
		vector<queue<int>> v(t);
		queue<int> q;
		for(i = 0; i < t; ++i) {
			cin >> a;
			for(j = 0; j < a; ++j) {
				cin >> b;
				mp[b] = i;
			}
		}
		while(cin >> s && s != "STOP") {
			if(s == "ENQUEUE") {
				cin >> a;
				if(v[mp[a]].empty()) {
					q.push(mp[a]);
					v[mp[a]].push(a);
				} else {
					v[mp[a]].push(a);
				}
			}
			if(s == "DEQUEUE") {
				cout << v[q.front()].front() << endl;
				v[q.front()].pop();
				if(v[q.front()].empty()) {
					q.pop();
				}
			}
		}
		cout << endl; 
	}
	return 0;
}
