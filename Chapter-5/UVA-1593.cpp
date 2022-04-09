#include<iostream>
#include<sstream>
#include<vector>
#include<string.h>
using namespace std;

int main() {
	vector<vector<string> > v;
	string line, word;
	int i, j, k;
	int vlen[200];
	while(getline(cin, line)) {
		stringstream ss(line);
		vector<string> vs;
		while(ss >> word) {
			vs.push_back(word);
		}
		v.push_back(vs);
	}
	memset(vlen, 0, 200);
	for(i = 0; i < v.size(); ++i) {
		for(j = 0; j < v[i].size(); ++j) {
			vlen[j] = v[i][j].length() > vlen[j] ? v[i][j].length() : vlen[j];
		}
	}
	for(i = 0; i < v.size(); ++i) {
		// if(i != 0) cout << endl; 
		for(j = 0; j < v[i].size(); ++j) {
			cout << v[i][j];
			if(j != v[i].size() - 1) {
				for(k = vlen[j] - v[i][j].size(); k > 0; --k) {
					cout << ' ';
				}
				cout << ' ';
			}
		}
		cout << endl; 
	}
	return 0;
}
