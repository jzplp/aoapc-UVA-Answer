#include<iostream>
#include<string>
#include<map>
#include<sstream>
using namespace std;

void getMap(map<string, string> & mp, string &line) {
	int i, j, k;
	for(i = 0; i < line.length(); ++i) {
		if((line[i] < 'a' || line[i] > 'z') && (line[i] < '0' || line[i] > '9')) {
			line[i] = ' ';
		}
	}
	stringstream ss(line);
	string word1, word2;
	while(ss >> word1 >> word2) {
		mp[word1] = word2;
	}
}

int main() {
	int n;
	bool flag[3];
	cin >> n;
	string line1, line2;
	getline(cin, line1);
	while(n--) {
		getline(cin, line1);
		getline(cin, line2);
		map<string, string> mp1, mp2;
		getMap(mp1, line1);
		getMap(mp2, line2);
		flag[0] = false;
		flag[1] = false;
		flag[2] = false;
		for(auto i = mp2.begin(); i !=mp2.end(); ++i) {
			if(!mp1.count(i->first)) {
				if(flag[0] == false) {
					flag[0] = true;
					cout << "+" << i->first;
				} else {
					cout << ',' << i->first;
				}
			}
		}
		if(flag[0] == true) {
			cout << endl;
		}
		for(auto i = mp1.begin(); i !=mp1.end(); ++i) {
			if(!mp2.count(i->first)) {
				if(flag[1] == false) {
					flag[1] = true;
					cout << "-" << i->first;
				} else {
					cout << ',' << i->first;
				}
			}
		}
		if(flag[1] == true) {
			cout << endl;
		}
		for(auto i = mp2.begin(); i !=mp2.end(); ++i) {
			if(mp1.count(i->first) && i->second != mp1[i->first]) {
				if(flag[2] == false) {
					flag[2] = true;
					cout << "*" << i->first;
				} else {
					cout << ',' << i->first;
				}
			}
		}
		if(flag[2] == true) {
			cout << endl;
		}
		if(!flag[0] && !flag[1] && !flag[2]) {
			cout << "No changes" << endl;
		}
		cout << endl;
	}
	return 0;
}
