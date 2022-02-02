#include<iostream>
#include<set>
#include<queue>

using namespace std;

int main() {
	set<long long> se;
	int arr[3] = {2,3,5};
	long long ll, llt;
	priority_queue<long long, vector<long long>, greater<long long> > pq;
	int i, j;
	se.insert(1);
	pq.push(1);
	for(i = 1; i < 1500; ++i) {
		ll = pq.top();
		pq.pop();
		for(j = 0; j < 3; ++j) {
			llt = ll * arr[j];
			if(se.count(llt) == 0) {
				se.insert(llt);
				pq.push(llt);
			}
		}
	}
	cout << "The 1500'th ugly number is " << pq.top() << '.' << endl;
	return 0;
} 
