#include<iostream>
#include<map>
#include<string>
#include<vector>

using namespace std;

int main() {
	int n, m , i, j, jj, num;
	int cnt;
	string sline, s;
	bool flag;
	while(cin >> n >> m) {
		vector<map<int, int>> mpPair((m+1)*(m+1));
		vector<vector<int> > v(n);
		map<string, int> mpNum;
		num = 0;
		getline(cin, sline);
		for(i = 0; i < n; ++i) {
			getline(cin, sline); 
			for(j = 0; j < sline.length(); ++j) {
				jj = sline.find(",", j);
				if(jj < 0) {
					jj = sline.length();
				}
				s = sline.substr(j, jj - j);
				if(mpNum.count(s) == 0) {
					mpNum[s] = num;
					++num;
				}
				v[i].push_back(mpNum[s]);
				j = jj;
			}
		}
		flag = false; 
		for(i = 0; i < n; ++i) {
			for(j = 0; j < m; ++j) {
				for(jj = j + 1; jj < m; ++jj) {
					cnt = v[i][j] * 100000 + v[i][jj];
					if(mpPair[(j+1) * m + (jj+1)].count(cnt) == 1) {
						cout << "NO" <<endl;
						cout <<  mpPair[(j+1) * m + (jj+1)][cnt] + 1 << " " << i + 1 << endl;
						cout <<  j + 1 << " " << jj + 1 << endl;
						flag = true;
						break;
					} else {
						mpPair[(j+1) * m + (jj+1)][cnt] = i;
					}
				}
				if(flag == true) {
					break;
				}
			}
			if(flag == true) {
				break;
			}
		}
		if(flag == false) {
			cout << "YES" << endl; 
		}
	}
	return 0;
}
