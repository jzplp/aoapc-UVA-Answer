#include<iostream>
#include<string>
#include<map>
#include<set>
using namespace std;

int main() {
	string s,st;
	int i,j,k,tmp;
	char c;
	map<char, string> chars;
	map<string, string> words;
	set<string> se;
	while(cin >> st) {
		if(st[0] == '*')
			break;
		cin >> s;
		chars[st[0]] = s;
	}
	while(cin >> st) {
		if(st[0] == '*')
			break;
		s = "";
		for(i=0; i!=st.size(); ++i) {
			s += chars[st[i]];
		}
		if(words.find(s) == words.end())
			words[s] = st;
		else {
			se.insert(s);
			//if(words[s].size() > st.size() || (words[s].size() == st.size() && st < words[s]))
			if(st < words[s])
				words[s] = st;
		}
	}
	while(cin >> st) {
		if(st[0] == '*')
			break;
		if(words.find(st) != words.end()) {
			cout << words[st];
			if(se.find(st) != se.end())
				cout << "!";
			cout << endl;
		} else {
			k = 200;
			s = words.begin()->second;
			for(auto ip = words.begin(); ip != words.end(); ++ip) {
				for(i=0; i<st.size(); ++i)
					if(ip->first.size() == i || ip->first[i] != st[i])
						break;
				if(ip->first.size() != i && st.size() != i)
					continue;
				tmp = st.size()-i+ip->first.size()-i;
				if(tmp < k || (k == tmp && ip->second < s)) {
					s = ip->second;
					k = tmp;
				}
			}
			cout << s << "?" << endl;
		}
	}
	return 0;
}
