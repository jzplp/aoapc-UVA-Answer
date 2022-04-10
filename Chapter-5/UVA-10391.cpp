#include<set>
#include<iostream>
#include<string>
using namespace std;

int main() {
	set<string> se;
	string s;
	int size, i;
	bool flag;
	while(cin >> s) {
		se.insert(s);
	}
	for(auto ip = se.begin(); ip != se.end(); ++ip) {
		size = ip->length() - 1;
		// cout << size << " " << *ip << endl;
		flag = false;
		for(i = 1; i < size; ++i) {
			string s1 = ip->substr(0, i);
			string s2 = ip->substr(i);
			if(se.count(s1) && se.count(s2)) {
				flag = true;
				break;
			}
		}
		if(flag == true) {
			cout << *ip << endl;
		}
	}
	return 0;
}
