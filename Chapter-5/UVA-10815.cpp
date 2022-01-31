#include<iostream>
#include<set>
#include<string>
#include<sstream>
#include<ctype.h>

using namespace std;

int main() {
	set<string> se;
	string s, st;
	while(cin >> s) {
		for(auto i = s.begin(); i !=s.end(); ++i) {
			if(isalpha(*i)) {
				*i = tolower(*i);
			} else {
				*i = ' ';
			}
		}
		stringstream ss(s);
		while(ss >> st) {
			se.insert(st); 
		}
	}
	for(auto i = se.begin(); i != se.end(); ++i) {
		cout << *i << endl;
	}
	return 0;
}
