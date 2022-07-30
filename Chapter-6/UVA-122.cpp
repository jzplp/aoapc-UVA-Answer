#include<stdio.h>
#include<string.h>
#include<queue>

using namespace std;

char s[10000]; 
struct Node {
	int v;
	int left, right;
};

Node arr[300];
int len = 0;
bool legal = true;

int createNode(int v) {
	arr[len].v = v;
	arr[len].left = 0;
	arr[len].right = 0;
	++len;
	return len - 1;
}

int input() {
	int v, i, j, n, ni;
	while(scanf("%s", s) > 0) {
		if(strcmp(s, "()") == 0) {
			return 0; 
		}
		sscanf(s+1, "%d", &v);
		j = strchr(s, ',') - s + 1; 
		n = strlen(s);
		ni = 0; 
		for(i = j; i < n; ++i) {
			if(s[i] == 'L') {
				if(arr[ni].left == 0) {
					arr[ni].left = createNode(0);
				}
				ni = arr[ni].left;
			}
			if(s[i] == 'R') {
				if(arr[ni].right == 0) {
					arr[ni].right = createNode(0);
				}
				ni = arr[ni].right;
			}
		}
		if(arr[ni].v != 0) {
			legal = false;
		}
		arr[ni].v = v;
	}
	return -1;
}


void output() {
	queue<int> qu;
	int i;
	qu.push(0);
	s[0] = 0; 
	while(!qu.empty()) {
		i = qu.front();
		qu.pop(); 
		if(arr[i].v == 0) {
			legal = false; 
			return;
		}
		sprintf(s + strlen(s), "%d ", arr[i].v);
		if(arr[i].left) {
			qu.push(arr[i].left);
		}
		if(arr[i].right) {
			qu.push(arr[i].right);
		}
	}
	s[strlen(s) - 1] = 0;
	printf("%s\n", s);
}


int main() {
	while(1) {
		len = 0;
		createNode(0);
		legal = true;
		if(input() == -1) {
			return 0;
		}
		if(legal == false) {
			printf("not complete\n");
			continue;
		}
		output();
		if(legal == false) {
			printf("not complete\n");
			continue;
		}
	}
}
