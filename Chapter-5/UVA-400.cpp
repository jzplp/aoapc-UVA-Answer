#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;
vector<string> v;

void print(const string &s, int ml, char c) {
	cout << s;
	int i = s.length();
	while(i < ml) {
		cout << c;
		++i; 
	}
} 

int main() {
	int n, i, j, k, ml;
	int row, col;
	string s;
	while(cin >> n && n > 0) {
		v.clear();
		ml = 0;
		for(i = 0; i < n; ++i) {
			cin >> s;
			v.push_back(s);
			ml = max((int)s.length(), ml);
		}
		sort(v.begin(), v.end());
		col = (60 + 2) / (ml + 2);
		row = n / col + (n % col ? 1 : 0);
		print("", 60, '-');
		cout << endl;
		for(i = 0; i < row; ++i) {
			for(j = 0; j < col; ++j) {
				k = j * row + i;
				if(k >= n) break; 
				if(j == col - 1) {
					cout << v[k];
				} else {
					print(v[k], ml+2, ' ');
				}
			}
			cout << endl; 
		}
	}
	return 0;
}
