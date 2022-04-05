#include<iostream>
#include<string>
#include<map>
#include<set>
#include<vector> 

using namespace std;

void getName(string iden, string &name, string &mta) {
	int n = iden.find('@');
	name = iden.substr(0, n);
	mta = iden.substr(n+1);
}

int main() {
	string s, mta, send, name, reci, data;
	string data_space = "     "; 
	string send_name, send_mta, reci_name, reci_mta;
	set<string> se;
	bool flag;
	int n, i, j;

	while(cin >> s && s != "*") {
		cin >> mta;
		cin >> n;
		while(n--) {
			cin >> name;
			se.insert(name + "@" + mta);
		}
	}

	while(cin >> send && send != "*") {
		getName(send, send_name, send_mta);
		
		vector<string> mta_v;
		map<string, vector<string> > reci_mp;
		set<string> reci_se;
		
		while(cin >> reci && reci != "*") {
			if(reci_se.count(reci)) continue;
			reci_se.insert(reci);
			
			getName(reci, reci_name, reci_mta);
			if(!reci_mp.count(reci_mta)) {
				mta_v.push_back(reci_mta);
				reci_mp[reci_mta] = vector<string>();
			}
			reci_mp[reci_mta].push_back(reci);
		}
		getline(cin, s);

		data = "";
		while(getline(cin, s) && s != "*") {
			data += data_space + s + "\n";
		}

		for(i = 0; i < mta_v.size(); ++i) {
			cout << "Connection between " << send_mta << " and "  << mta_v[i] << endl;
			cout << data_space << "HELO " << send_mta << endl;
			cout << data_space << 250 << endl;
			cout << data_space << "MAIL FROM:<" << send << ">" << endl;
			cout << data_space << 250 << endl;
			flag = false;
			for(j = 0; j < reci_mp[mta_v[i]].size(); ++j) {
				cout << data_space << "RCPT TO:<" << reci_mp[mta_v[i]][j] << ">" << endl;
				if(se.count(reci_mp[mta_v[i]][j])) {
					flag = true;
					cout << data_space << 250 << endl;
				} else {
					cout << data_space << 550 << endl;
				}
			}
			if(flag) {
				cout << data_space << "DATA" << endl;
				cout << data_space << 354 << endl;
				cout << data;
				cout << data_space << "." << endl;
				cout << data_space << 250 << endl;
			}
			cout << data_space << "QUIT" << endl;
			cout << data_space << 221 << endl;
		}
	}
	return 0;
} 







