#include<iostream>
#include<string>
#include<stack>

using namespace std;

struct Metrix {
	int a, b;
};

int cal(stack<Metrix> & st) {
	Metrix m1, m2;
	m2 = st.top();
	st.pop();
	m1 = st.top();
	st.pop();
	if(m1.b != m2.a) {
		return -1; 
	}
	st.push({m1.a, m2.b});
	return m1.a * m1.b * m2.b; 
}

int main() {
	int n, i, j, k;
	string s;
	Metrix v[28];
	cin >> n;
	bool flag;
	while(n--) {
		cin >> s;
		k = s[0] - 'A';
		cin >> i >> j;
		v[k].a = i;
		v[k].b = j;
	}
	while(cin >> s) {
		stack<Metrix> st;
		flag = true;
		int sum = 0, t;
		for(auto ip = s.begin(); flag && ip != s.end(); ++ip) {
			if(*ip >= 'A' && *ip <= 'Z') {
				st.push(v[*ip - 'A']);
			}
			if(*ip == ')' && st.size() > 1) {
				t = cal(st);
				if(t < 0) {
					flag = false;
					break;
				}
				sum += t;
			}
		}
		while(flag && st.size() > 1) {
			t =  cal(st);
			if(t < 0) {
				flag = false;
				break;
			}
			sum += t;
		}
		if(flag) {
			cout << sum << endl;
		} else {
			cout << "error" << endl;
		}
	}
	return 0;
}
