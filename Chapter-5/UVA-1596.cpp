#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<stdlib.h>
#include<stack>
#define MAX 60
using namespace std;

struct Array {
	int size;
	map<int, int> mp;
};

Array arr[MAX];
int bug;

int getValue(string s) {
	stack<int> st;
	int a = 0, av = 0;
	while(s.length()) {
		if(s[0] >= 'A' && s[0] <= 'z') {
			st.push(s[0] - 'A');
			s = s.substr(2, s.length() - 3);
		} else {
			av = atoi(s.c_str());
			break;
		}
	}
	while(st.size()) {
		a = st.top();
		if(av >= arr[a].size || !arr[a].mp.count(av)) {
			bug = 1;
			return 0;
		}
		av =  arr[a].mp[av];
		st.pop();
	}
	return av;
}

void handleDecl(string line) {
	Array a;
	int i = line[0] - 'A';
	if(i < 0 || i > MAX) {
		bug = 1;
		return;
	} 
	line = line.substr(2, line.length() - 3);
	int num = atoi(line.c_str());
	a.size = num;
	arr[i] = a;
}

void handlAssi(string line) {
	int cut = line.find("=");
	string front, after;
	front = line.substr(0, cut);
	after = line.substr(cut + 1);
	int a1, v1, v2;
	a1 = front[0] - 'A';
	if(a1 < 0 || a1 > MAX) {
		bug = 1;
		return;
	} 
	v1 = getValue(front.substr(2, front.length() - 3));
	if(bug) {
		return;
	}
	if(v1 >= arr[a1].size) {
		bug = 1;
		return;
	}
	v2 = getValue(after);
	if(bug) {
		return;
	}
	arr[a1].mp[v1] = v2;
}

void handleLine(string line) {
	int pos = line.find("=");
	if(pos < 0) {
		handleDecl(line);
	} else {
		handlAssi(line);
	}
}


int main() {
	string line;
	int i, j, k, lineNum;
	while(getline(cin, line) && line != ".") {
		for(i = 0; i < MAX; ++i) {
			arr[i].size = 0;
			arr[i].mp.clear();
		}
		bug = 0;
		lineNum = 1;
		handleLine(line);
		while(getline(cin, line) && line != ".") {
			if(!bug) {
				++lineNum;
				handleLine(line);
			}
		}
		if(!bug) {
			lineNum = 0;
		}
		cout << lineNum << endl;
	}
	return 0;
}
