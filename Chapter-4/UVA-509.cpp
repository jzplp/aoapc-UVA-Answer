#include<stdio.h>
#include<string.h>
int d, s, b;
char arr[6][64000];
char sign[10];
char res[64000];
int resi;
char con[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'}; 

bool judge(int x) {
	int k, c = 0, xloc;
	int xflag = false;
	for(k = 0; k < d; ++k) {
		if(arr[k][x] == 'x') {
			if(xflag == true) return false;
			if(xflag == false) {
				xflag = true;
				xloc = k;
			}
			continue;
		}
		c += arr[k][x] - '0';
	}
	c = c % 2;
	if(xflag == true) {
		arr[xloc][x] = (sign[0] == 'E' ? c : !c) + '0';
	} else {
		if((sign[0] == 'E' && c == 1) || (sign[0] == 'O' && c == 0)) {
			return false; 
		}
	}
	return true; 
}

bool isVaild() {
	int i, j, k, t, x;
	for(i = 0; i < b; ++i) {
		t = i % d;
		for(j = 0; j < s; ++j) {
			x = i * s + j;
			if(judge(x) == false) {
				return false;
			}
		}
		for(k = 0; k < d; ++k) {
			if(k == t) continue;
			strncpy(res+resi, &arr[k][i*s], s);
			resi += s; 
		}
	}
	return true;
}

void convert() {
	int i, j = 0;
	for(i = 0; i < resi; ++i) { 
		j = j * 2 + res[i] - '0';
		if(i % 4 == 3) {
			printf("%c", con[j]);
			j = 0;
		}
	}
	if(i % 4 == 0) return;
	while(i % 4 != 0) {
		j = j * 2;
		++i;
	}
	printf("%c", con[j]);
}

int main() {
	int i, count = 0;
	int t, x, c;
	while(scanf("%d%d%d", &d, &s, &b) == 3 && d != 0) {
		scanf("%s", sign);
		for(i = 0; i < d; ++i) {
			scanf("%s", arr[i]);
		}
		printf("Disk set %d is ", ++count);
		resi = 0;
		if(isVaild()) {
			printf("valid, contents are: ");
			convert();
			putchar('\n'); 
		} else {
			puts("invalid.");
		}
	}
	return 0;
}