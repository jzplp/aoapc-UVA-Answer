#include<iostream>
#include<string>
#include<string.h>
#include<deque>
#include<queue>
#include<vector>
#include<stdlib.h> 
using namespace std;

int values[30];
deque<int> readys;
queue<int> blocks;
struct PROM {
	vector<string> lines;
	int cur;
};
vector<PROM> pros;
int stateTime[5] = {};
int quantum;

void init() {
	memset(values, 0, 30*sizeof(int));
	pros.clear();
	readys.clear();
	blocks = queue<int>();
	memset(stateTime, 0, 5*sizeof(int));
	quantum = 0;
}

void inputs() {
	string line;
	int t, i, j, k;
	cin >> t;
	for(i = 0; i < 5; ++i) {
		cin >> stateTime[i];
	}
	cin >> quantum;
	getchar();
	for(i = 0; i < t; ++i) {
		PROM p;
		p.cur = 0;
		do {
			getline(cin, line);
			p.lines.push_back(line);
		} while(line != "end");
		pros.push_back(p);
		readys.push_back(i);
	}
}

void assignment(string line) {
	int a = line[0] - 'a';
	values[a] = atoi(line.substr(4).c_str());
}

void print(int cnt, char c) {
	cout << cnt+1 << ": " << values[c - 'a'] << endl;
}

void compute() {
	int cnt, cntTime, i, j, k;
	bool lockFlag = false, noReady;
	string line;
	while(!readys.empty()) {
		cnt = readys.front();
		readys.pop_front();
		cntTime = quantum;
		noReady = false;
		while(cntTime > 0) {
			line = pros[cnt].lines[pros[cnt].cur++];
			if(line == "end") {
				noReady = true;
				break;
			}
			if(line[2] == '=') {
				assignment(line);
				cntTime -= stateTime[0];
			}
			if(line[1] == 'r') {
				print(cnt, line[6]);
				cntTime -= stateTime[1];
			}
			if(line == "lock") {
				cntTime -= stateTime[2];
				if(lockFlag == false) {
					lockFlag = true;
				} else {
					--pros[cnt].cur;
					blocks.push(cnt);
					noReady = true;
					break;
				}
			}
			if(line == "unlock") {
				cntTime -= stateTime[3];
				lockFlag = false;
				if(!blocks.empty()) {
					k = blocks.front();
					blocks.pop(); 
					readys.push_front(k);
				}
			}
		}
		if(noReady == false) {
			readys.push_back(cnt);
		}
	}
}

int main() {
	int t, i, j;
	cin >> t;
	while(t--) {
		init();
		inputs();
		compute();
		if(t) cout << endl;
	}
	return 0; 
}
