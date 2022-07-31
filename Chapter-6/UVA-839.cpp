#include<stdio.h>

bool flag;

int input() {
	int wl, dl, wr, dr;
	scanf("%d %d %d %d", &wl, &dl, &wr, &dr);
	if(!wl) {
		wl = input();
	}
	if(!wr) {
		wr = input();
	}
	if(wl * dl != wr * dr) {
		flag = false;
	}
	return wl + wr;
}

int main() {
	int t, i;
	scanf("%d", &t);
	for(i = 0; i < t; ++i) {
		if(i != 0) {
			putchar('\n');
		}
		flag = true;
		input();
		if(flag) {
			printf("YES\n");
		} else {
			printf("NO\n");
		}
	}
}
