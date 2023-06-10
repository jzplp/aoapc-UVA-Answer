#include<stdio.h>
#include<string.h>
#include<map>
using namespace std;

struct NtNode {
	map<int, int> in;
	map<int, int> out;
};

int main() {
	int n = 0, np, nt, nf;
	int i ,j, k;
	bool flagDead, flagTran;
	int num;
	while(scanf("%d", &np) == 1 && np > 0) {
		int npArr[110];
		NtNode ntArr[110];
		++n;
		for(i = 1; i <= np; ++i) {
			scanf("%d", &npArr[i]);
		}
		scanf("%d", &nt);
		for(i = 1; i <= nt; ++i) {
			while(scanf("%d", &k) == 1 && k != 0) {
				if(k > 0) ntArr[i].out[k] = ntArr[i].out[k] + 1;
				else ntArr[i].in[-k] = ntArr[i].in[-k] + 1;
			}
		}
		scanf("%d", &nf);
		num = 0;
		while(1) {
			flagDead = false;
			for(i = 1; i <= nt; ++i) {
				flagTran = true;
				for(auto ip = ntArr[i].in.begin(); ip != ntArr[i].in.end(); ++ip) {
					if(npArr[ip->first] < ip->second) flagTran = false;
				}
				if(!flagTran) continue;
				for(auto ip = ntArr[i].in.begin(); ip != ntArr[i].in.end(); ++ip) {
					npArr[ip->first] -= ip->second;
				}
				for(auto ip = ntArr[i].out.begin(); ip != ntArr[i].out.end(); ++ip) {
					npArr[ip->first] += ip->second;
				}
				flagDead = true;
				++num;
				if(num == nf) break;
			}
			if(num == nf || !flagDead) break;
		}
		printf("Case %d: ", n);
		if(num != nf) {
			printf("dead after %d transitions\n", num);
		} else {
			printf("still live after %d transitions\n", num);
		}
		printf("Places with tokens:");
		for(i = 1; i <= np; ++i) {
			if(npArr[i]) {
				printf(" %d (%d)", i, npArr[i]);
			}
		}
		printf("\n\n");
	}
	return 0;
}
