#include<iostream>
#include<string>
#include<sstream>
#define MAXN 10010
using namespace std;

struct Node {
	int v;
	int left, right;
};

Node tree[MAXN];
int inorder[MAXN];
int postorder[MAXN];
int len, treeLen;

int minv, mini;


int inputline(int *p) {
	len = 0;
	int i;
	string s;
	if(!getline(cin, s)) {
		return 0;
	}
	stringstream sin(s);
	while(sin >> i) {
		p[len++] = i;
	}
	return len;
}

int createNode(int v) {
	tree[treeLen].v = v;
	tree[treeLen].left = 0;
	tree[treeLen].right = 0;
	return treeLen++;
}

int buildTree(int l1, int r1, int l2, int r2) {
	if(l1 > r1) {
		return 0;
	}
	int root = createNode(postorder[r2]);
	int i = l1;
	while(inorder[i] != tree[root].v && i <= r1) {
		++i;
	}
	tree[root].left = buildTree(l1, i - 1, l2, l2 + i - 1 - l1);
	tree[root].right = buildTree(i + 1, r1, l2 + i - l1, r2 - 1);
	return root;
}

void traver(int p, int sum) {
	sum += tree[p].v;
	if(!tree[p].left && !tree[p].right) {
		if(sum < minv || (sum == minv && mini > tree[p].v)) {
			minv = sum;
			mini = tree[p].v;
		}
	}
	if(tree[p].left) {
		traver(tree[p].left, sum);
	}
	if(tree[p].right) {
		traver(tree[p].right, sum);
	}
}

int main() {
	while(inputline(inorder)) {
		inputline(postorder);
		treeLen = 0;
		minv = 100000001;
		buildTree(0, len - 1, 0, len - 1);
		traver(0, 0);
		cout << mini << endl;
	}
}
