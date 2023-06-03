#include<stdio.h>
#include<string.h>

char preord[30];
char inord[30];
char postord[30];
int posti;

struct Node {
	char c;
	Node * left, * right;
};

Node * getTree(int begpre, int endpre, int begin, int endin) {
	int i;
	if(begpre > endpre) return NULL;
	Node * p = new Node();
	p->c = preord[begpre];
	p->left = NULL;
	p->right = NULL;
	if(begpre == endpre) {
		return p;
	}
	for(i = begin; i != endin; ++i) {
		if(preord[begpre] == inord[i]) break;
	}
	int leftLen = i - begin;
	int rightLen = endin - i;
	if(leftLen != 0) {
		p->left = getTree(begpre + 1, begpre + leftLen, begin, i - 1);
	}
	if(rightLen != 0) {
		p->right = getTree(begpre + leftLen + 1, endpre, i + 1, endin);
	}
	return p;
}

void postTra(Node * p) {
	if(!p) return;
	if(p->left) {
		postTra(p->left);
	}
	if(p->right) {
		postTra(p->right);
	}
	postord[posti++] = p->c;
	delete p;
}

int main() {
	int len;
	while(scanf("%s %s", preord, inord) == 2) {
		len = strlen(preord);
		Node * tree;
		tree = getTree(0, len - 1, 0, len - 1);
		posti = 0;
		postTra(tree);
		postord[posti] = 0;
		printf("%s\n", postord);
	}
	return 0;
}

