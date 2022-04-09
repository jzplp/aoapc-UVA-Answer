#include<iostream>
#include<math.h>
#include<string.h>
using namespace std;

int arr[1005][2005];
int n;

int judge(int i) {
	int j, k;
	for(j = 0; j < n; ++j) {
		if(arr[i][j] != 0) {
			break;
		}
	}
	if(j == n) {
		return 1;
	}
	for(k = 0; k < i; ++k) {
		for(j = 0; j < n; ++j) {
			if(arr[i][j] != arr[k][j]) {
				break;
			}
		}
		if(j == n) {
			return 2;
		}
	}
	return 0;
}

int main() {
	int m,i,j,k;
	int flag;
	cin >> m;
	while(m--) {
		memset(arr, 0, 1005*2005);
		cin >> n;
		for(i = 0; i < n; ++i) {
			cin >> arr[0][i];
		}
		i = 0;
		while(1) {
			flag = judge(i);
			if(flag != 0) {
				break;
			}
			++i;
			arr[i][n-1] = abs(arr[i-1][0] - arr[i-1][n-1]);
			for(j = 1; j < n; ++j) {
				arr[i][j-1] = abs(arr[i-1][j] - arr[i-1][j-1]);
			}
		}
		if(flag == 1) {
			cout << "ZERO" << endl;
		} else {
			cout << "LOOP" << endl;
		}
	}
}
