#include<string>
#include<string.h>
#include<map>
#include<vector>
#include<iostream>
#include<sstream>
#include<algorithm>

#define MAXN 10000
using namespace std;

int n;
map<string, int> mpName;
string vecName[MAXN];
vector<int> vecDepend[MAXN];
vector<int> vecDepend2[MAXN];
int vecInstall[MAXN];
vector<int> vecList;

int getNum(const string & word) {
	if(mpName.count(word)) {
		return mpName[word];
	}
	vecName[++n] = word;
	mpName[word] = n;
	return n;
}

void handleDepend(stringstream & ss) {
	string word;
	ss >> word;
	int num = getNum(word);
	int num2;
	while(ss >> word) {
		num2 = getNum(word);
		vecDepend[num].push_back(num2);
		vecDepend2[num2].push_back(num);
	}
}

void installNum(int num, int type) {
	int i;
	for(i = 0; i < vecDepend[num].size(); ++i) {
		if(!vecInstall[vecDepend[num][i]]) {
			installNum(vecDepend[num][i], 1);
		}
	}
	vecInstall[num] = type;
	vecList.push_back(num);
	cout <<  "   Installing " << vecName[num] << endl;
}

void handleInstall(const string & word) {
	int num = getNum(word);
	if(vecInstall[num]) {
		cout << "   " << word << " is already installed." << endl;
		return;
	}
	installNum(num, 2);
}

void removeListNum(int num) {
	vecList.erase(find(vecList.begin(), vecList.end(), num));
}

void removeNum(int num) {
	int i;
	for(i = 0; i < vecDepend2[num].size(); ++i) {
		if(vecInstall[vecDepend2[num][i]]) {
			return;
		}
	}
	vecInstall[num] = 0;
	removeListNum(num);
	cout << "   Removing " << vecName[num] << endl;
	for(i = 0; i < vecDepend[num].size(); ++i) {
		if(vecInstall[vecDepend[num][i]] == 1) {
			removeNum(vecDepend[num][i]);
		}
	}
}

void handleRemove(const string & word) {
	int num = getNum(word);
	int i;
	if(!vecInstall[num]) {
		cout << "   " << word << " is not installed." << endl;
		return;
	}
	for(i = 0; i < vecDepend2[num].size(); ++i) {
		if(vecInstall[vecDepend2[num][i]]) {
			cout << "   " << vecName[num] << " is still needed." << endl;
			return;
		}
	}
	vecInstall[num] = 0;
	removeListNum(num);
	cout << "   Removing " << vecName[num] << endl;
	for(i = 0; i < vecDepend[num].size(); ++i) {
		if(vecInstall[vecDepend[num][i]] == 1) {
			removeNum(vecDepend[num][i]);
		}
	}
}

void handleList() {
	int i;
	for(i = 0; i < vecList.size(); ++i) {
		cout << "   " << vecName[vecList[i]] << endl;
	}
}

int main() {
	string com;
	string line, word;
	n = 0;
	memset(vecInstall, 0, sizeof(vecInstall));
	while(getline(cin, line)) {
		cout << line << endl;
		stringstream ss(line);
		ss >> com;
		if(com[0] == 'D') {
			handleDepend(ss);
		}
		else if(com[0] == 'I') {
			ss >> word;
			handleInstall(word);
		}
		else if(com[0] == 'R') {
			ss >> word;
			handleRemove(word);
		}
		else if(com[0] == 'L') {
			handleList();
		}
		else if(com[0] == 'E') {
			break;
		}
	}
	return 0;
}
