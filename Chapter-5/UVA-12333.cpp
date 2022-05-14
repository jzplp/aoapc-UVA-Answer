#include<stdio.h>
#include<string.h>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

struct BigInt {
	static const long long BASE = 1000000000000000000;
	static const int WIDTH = 18;
	static const int LEN = 4;
	
	vector<long long> s;
	BigInt(long long num = 0) {
		*this = num;
	}
	BigInt operator= (long long num) {
		s.clear();
		do {
			s.push_back(num % BASE);
			num /= BASE;
		} while(num > 0);
		return *this;
	}
	BigInt operator+ (const BigInt &b) {
		BigInt c;
		c.s.clear();
		long long g = 0, x;
		int ssize = s.size(), bssize = b.s.size();
		for(int i = 0; ; i++) {
			if(g == 0 && i >= ssize && i >= bssize) break;
			x = g;
			if(i < ssize) x += s[i];
			if(i < bssize) x += b.s[i];
			c.s.push_back(x % BASE);
			g = x / BASE;
		}
		return c;
	}
	string outN() {
		string str, st;
		int i = s.size() - 1, j = LEN;
		while(i >= 0 && j > 0) {
			st = to_string(s[i]);
			while(i != s.size() - 1 && st.length() < WIDTH) {
				st = "0" + st;
			}
			str += st;
			--i;
			--j;
		}
		return str.substr(0, 40); 
	}
};

struct Node {
	int id;
	int num;
	Node* childs[10] = {NULL};
};

vector<string> v;

Node* createTree() {
	int i, j, n, num;
	Node * tree = new Node;
	tree->id = -1;
	tree->num = -1;
	for(i = 0; i < v.size(); ++i) {
		n = v[i].size();
		Node *p = tree;
		for(j = 0; j < n; ++j) {
			num = v[i][j] - '0';
			if(!p->childs[num]) {
				p->childs[num] = new Node;
				p->childs[num]->id = i;
				p->childs[num]->num = num;
			}
			p = p->childs[num];
		}
	}
	return tree;
}

int main() {
	char s[45];
	int i, j, T, n, num, res;
	BigInt bv[3];
	bv[0] = 1;
	bv[1] = 1;
	v.push_back("1");
	v.push_back("1");
	for(i = 2; i < 100000; ++i) {
		bv[i % 3] = bv[(i-1) % 3] + bv[(i-2) % 3];
		v.push_back(bv[i % 3].outN());
	}
	scanf("%d", &T);
	
	Node * tree = createTree();
	
	for(i = 0; i < T; ++i) {
		scanf("%s", s);
		n = strlen(s);
		Node * p = tree;
		for(j = 0; j < n; ++j) {
			num = s[j] - '0';
			if(!p->childs[num]) {
				break;
			}
			p = p->childs[num];
		}
		if(j == n) {
			res = p->id; 
		} else {
			res = -1;
		}
		printf("Case #%d: %d\n", i+1, res);
	} 
	return 0;
}
