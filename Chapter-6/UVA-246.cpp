#include<stdio.h>
#include<deque>
#include<vector>
#include<set>
using namespace std;

vector<deque<int>> vec;
set<vector<deque<int>>> se;
int gameNum;

int stepPlus(int step) {
	step = step + 1;
	if(step == 8) step = 1;
	return step;
}

void handlePile(int step) {
	int num, k1, k2, k3;
	while(1) {
		num = vec[step].size();
		if(num < 3) return;
		if((vec[step][0] + vec[step][1] + vec[step][num - 1]) % 10 == 0) {
			k1 = vec[step].front();
			vec[step].pop_front();
			vec[0].push_back(k1);
			k1 = vec[step].front();
			vec[step].pop_front();
			vec[0].push_back(k1);
			k1 = vec[step].back();
			vec[step].pop_back();
			vec[0].push_back(k1);
			continue;
		}
		if((vec[step][0] + vec[step][num - 1] + vec[step][num - 2]) % 10 == 0) {
			k1 = vec[step].front();
			vec[step].pop_front();
			vec[0].push_back(k1);
			k2 = vec[step].back();
			vec[step].pop_back();
			k3 = vec[step].back();
			vec[step].pop_back();
			vec[0].push_back(k3);
			vec[0].push_back(k2);
			continue;
		}
		if((vec[step][num - 3] + vec[step][num - 1] + vec[step][num - 2]) % 10 == 0) {
			k1 = vec[step].back();
			vec[step].pop_back();
			k2 = vec[step].back();
			vec[step].pop_back();
			k3 = vec[step].back();
			vec[step].pop_back();
			vec[0].push_back(k3);
			vec[0].push_back(k2);
			vec[0].push_back(k1);
			continue;
		}
		return;
	}
}


int handleGame() {
	int k;
	int step = 1;
	while(!vec[0].empty()) {
		++gameNum;
		k = vec[0].front();
		vec[0].pop_front();
		while(vec[step].empty()) step = stepPlus(step);
		vec[step].push_back(k);
		handlePile(step);
		// draw
		if(se.count(vec)) return 0;
		se.insert(vec);
		step = stepPlus(step);
		if(vec[0].size() == 52) {
			// win
			return 1; 
		}
	}
	// lose
	return -1;
} 

int main() {
	int k, i, j;
	while(scanf("%d", &k) == 1 && k != 0) {
		gameNum = 7;
		vec.clear();
		se.clear();
		vec.push_back(deque<int>());
		vec.push_back(deque<int>());
		vec[1].push_back(k);
		for(i = 2; i < 8; ++i) {
			scanf("%d", &k);
			vec.push_back(deque<int>());
			vec[i].push_back(k);
		}
		for(i = 8; i <= 52; ++i) {
			scanf("%d", &k);
			vec[0].push_back(k);
		}
		k = handleGame();
		switch(k) {
			case -1: printf("Loss"); break;
			case  0: printf("Draw"); break;
			case  1: printf("Win "); break;
		}
		printf(": %d\n", gameNum);
	}
	return 0;
}
