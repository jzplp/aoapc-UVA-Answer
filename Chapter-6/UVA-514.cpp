#include<iostream>
#include<stack>
#include<string>
using namespace std;

int N;

int handle() {
	int i, j, k, t;
	bool flag;
	stack<int> st;
	j = 1; 
	for(i = 0; i < N; ++i) {
		cin >> t;
		flag = false;
		if(t == 0) {
			return 0;
		}
		if(st.size() != 0 && st.top() == t) {
			st.pop();
			continue;
		}
		while(j <= N) {
			if(j == t) {
				++j;
				flag = true;
				break;
			}
			st.push(j);
			++j;
		}
		if(flag == true) {
			continue;
		}
		cout <<"No" << endl;
		return 1;
	}
	cout << "Yes" << endl; 
	return 1;
}

int main() {
	string s;
	while(cin >> N && N > 0) {
		while(handle()) {
			getline(cin, s);
		}
		cout << endl;
	}
	return 0;
}
