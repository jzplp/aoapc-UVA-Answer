#include<iostream>
#include<map>
#include<set>
#include<string>
#include<ctype.h>
#include<algorithm>
using namespace std;

string convert(string s) {
	for(auto i = s.begin(); i != s.end(); ++i) {
		*i= tolower(*i); 
	}
	sort(s.begin(), s.end());
	return s;
}

int main() {
	string s;
	map<string, int> m;
	set<string> se;
	while(cin >> s && s != "#") {
		se.insert(s);
		string st = convert(s);
		if(m.count(st) == 0) {
			m[st] = 1;
		} else {
			m[st]++;
		}
	}
	for(auto i = se.begin(); i != se.end(); ++i) {
		if(m[convert(*i)] == 1) {
			cout << *i << endl;
		}
	}
	return 0;
}
