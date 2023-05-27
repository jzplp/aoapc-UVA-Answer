#include<iostream>
#include<stack>
#include<string>
using namespace std; 

string line;

bool judge() {
	int i, j, k;
	char c;
	stack<char> st;
	for(i = 0; i < line.length(); ++i) {
		switch(line[i]) {
			case '(':
			case '[':
				st.push(line[i]);
				break;
			case ')':
				if(st.empty()) return false;
				c = st.top();
				if(c != '(') return false;
				st.pop();
				break;
			case ']':
				if(st.empty()) return false;
				c = st.top();
				if(c != '[') return false;
				st.pop();
				break;
		}
	}
	if(st.empty()) return true;
	return false;
} 

int main() {
	int n, i;
	cin >> n;
	getline(cin, line);
	while(n--) {
		getline(cin, line);
		cout << (judge()? "Yes" : "No") << endl;
	}
	return 0;
}
