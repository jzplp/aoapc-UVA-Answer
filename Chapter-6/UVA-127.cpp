#include<stdio.h>
#include<stack>
using namespace std;

char word[4];
stack<int> arr[55];

int handleOne() {
	return (word[0] << 8) + word[1];
}

bool judgeOne(int a, int b) {
	return (a % 256 == b % 256) || (a / 256 == b / 256);
} 

void handleCards() {
	bool changeFlag;
	int i, j, k;
	int num1, num3;
	while(1) {
		changeFlag = false;
		for(i = 1; i < 52; ++i) {
			if(arr[i].empty()) continue;
			k = 0; num1 = -1; num3 = -1;
			for(j = i-1; j >= 0; --j) {
				if(arr[j].empty()) continue;
				++k;
				if(k == 1) {
					num1 = j;
				}
				if(k == 3) {
					num3 = j;
					break;
				}
			}
			if(num3 >= 0 && judgeOne(arr[i].top(), arr[num3].top())) {
				arr[num3].push(arr[i].top());
				arr[i].pop();
				changeFlag = true;
				break;
			}
			if(num1 >= 0 && judgeOne(arr[i].top(), arr[num1].top())) {
				arr[num1].push(arr[i].top());
				arr[i].pop();
				changeFlag = true;
				break;
			}
		}
		if(!changeFlag) return;
	}
}

void outputCards() {
	int num = 0, i;
	int arrNum[52]; 
	for(i = 0; i < 52; ++i) {
		if(!arr[i].empty())
			++num;
	}
	printf("%d pile", num);
	if(num > 1) putchar('s');
	printf(" remaining:");
	for(i = 0; i < 52; ++i) {
		if(!arr[i].empty())
			printf(" %d", arr[i].size());
	}
	putchar('\n');
}

int main() {
	int i, j, k, a;
	while(scanf("%s", word) == 1 && word[0] != '#') {
		a = handleOne();
		arr[0] = stack<int>();
		arr[0].push(a);
		for(i = 1; i < 52; ++i) {
			scanf("%s", word);
			a = handleOne();
			arr[i] = stack<int>();
			arr[i].push(a);
		}
		handleCards();
		outputCards();
	}
	return 0;
} 
