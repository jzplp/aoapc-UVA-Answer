#include<string>
#include<iostream>
#include<set>
#include<map>
#include<vector>
#include<stack>
#include<algorithm>

using namespace std;

map<set<int>, int> mp;
vector<set<int>> v;
stack<int> st;

int findId(set<int> sse) {
	if(!mp.count(sse)) {
		v.push_back(sse);
		mp[sse] = v.size() - 1;
	}
	return mp[sse];
}

int main() {
	int t, n, i;
	string s;
	cin >> t;
	while(t--) {
		cin >> n;
		while(n--) {
			cin >> s;
			if(s == "PUSH") {
				st.push(findId(set<int>()));
			} else if(s == "DUP") {
				st.push(st.top());
			} else {
				int id1 = st.top();
				st.pop();
				int id2 = st.top();
				st.pop();
				set<int> sse;
				if(s == "UNION") {
					set_union(v[id1].begin(), v[id1].end(), v[id2].begin(), v[id2].end(), inserter(sse, sse.begin()));
					st.push(findId(sse));
				}
				if(s == "INTERSECT") {
					set_intersection(v[id1].begin(), v[id1].end(), v[id2].begin(), v[id2].end(), inserter(sse, sse.begin()));
					st.push(findId(sse));
				}
				if(s == "ADD") {
					sse = v[id2];
					sse.insert(id1);
					st.push(findId(sse));
				}
			}
			cout << v[st.top()].size() << endl;
		}
		cout << "***" << endl;
	}
	return 0;
} 
