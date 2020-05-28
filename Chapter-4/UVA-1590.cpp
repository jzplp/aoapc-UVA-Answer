#include<cstdio>

unsigned int arr[1010];
int iparr[4];

int main() {
	int m,i,j,k;
	unsigned int ip,mask,maski,net;
	while(scanf("%d", &m) == 1) {
		for(i=0; i<m; ++i) {
			scanf("%d.%d.%d.%d", iparr, iparr+1, iparr+2, iparr+3);
			arr[i] = 0;
			for(j=0; j<4; ++j) {
				arr[i] <<= 8;
				arr[i] |= iparr[j];
			}
			if(i == 0) {
				mask = -1;
				maski = 0;
				net = arr[0] & mask;
			} else {
				while(net != (arr[i] & mask)) {
					maski++;
					mask = ~((1 << maski) - 1);
					if(maski == 32)
						mask = 0;
					net = net & mask;
				}
			}
		}
		for(i=3; i>=0; --i) {
			iparr[i] = net % 256;
			net >>= 8;
		}
		printf("%d.%d.%d.%d\n", iparr[0], iparr[1], iparr[2], iparr[3]);
		for(i=3; i>=0; --i) {
			iparr[i] = mask % 256;
			mask >>= 8;
		}
		printf("%d.%d.%d.%d\n", iparr[0], iparr[1], iparr[2], iparr[3]);
	}
	return 0;
}
