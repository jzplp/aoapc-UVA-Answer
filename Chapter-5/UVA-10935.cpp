#include<queue>
#include<iostream>
using namespace std;

int main() {
	int n, i, j, k;
	while(cin >> n && n) {
		queue<int> qu;
		for(i = 1; i <= n; ++i) {
			qu.push(i);
		}
		cout << "Discarded cards:";
		while(qu.size() > 1) {
			cout << " " << qu.front();
			if(qu.size() > 2) {
				cout << ",";
			}
			qu.pop();
			j = qu.front();
			qu.pop();
			qu.push(j); 
		}
		cout << endl;
		cout << "Remaining card: " << qu.front() << endl;
	}
	return 0;
}
