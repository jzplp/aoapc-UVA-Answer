#include<stdio.h>
int initArr[10][3];
int arr[10][3];
int stu;

bool allAwaken() {
	int i;
	for(i = 0; i < stu; ++i) {
		if(arr[i][2] > arr[i][0]) return false;
	}
	return true;
}

bool sameInit() {
	int i, j;
	for(i = 0; i < stu; ++i) {
		for(j = 0; j < 3; ++j) {
			if(arr[i][j] != initArr[i][j]) {
				return false;
			}
		}
	}
	return true;
}

void trans() {
	int weaken = 0, sleep = 0;
	int i, j;
	for(i = 0; i < stu; ++i) {
		if(arr[i][2] > arr[i][0]) {
			++sleep;
		} else {
			++weaken;
		}
	}
	for(i = 0; i < stu; ++i) {
		if(arr[i][2] == arr[i][0]) {
			if(sleep > weaken) {
				++arr[i][2];
			} else {
				arr[i][2] = 1;
			}
		} else if(arr[i][2] == arr[i][0] + arr[i][1]) {
			arr[i][2] = 1;
		} else {
			arr[i][2]++;
		}
	}
}

int main() {
	int i, j, k, n = 0, t;
	while(scanf("%d", &stu) == 1 && stu != 0) {
		for(i = 0; i < stu; ++i) {
			scanf("%d%d%d", &initArr[i][0], &initArr[i][1], &initArr[i][2]);
			arr[i][0] = initArr[i][0];
			arr[i][1] = initArr[i][1];
			arr[i][2] = initArr[i][2];
		}
		t = 0;
		for(i = 1; 1; ++i) {
			if(allAwaken()) {
				break;
			}
			if(i != 1 && sameInit()) {
				t = -1;
				break;
			}
			trans();
		}
		printf("Case %d: %d\n", ++n, t == -1 ? -1 : i);
	}
}