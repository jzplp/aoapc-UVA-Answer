#include<stdio.h>

int main() {
	int j = 0, n, num, i, k, len, lent, it;
	char word[1000]; 
	int order[10];
	int terminal[1000];
	while(scanf("%d", &n) == 1 && n > 0) {
		++j;
		for(i = 0; i < n; ++i) {
			scanf("%s", word);
			k = word[1] - '0';
			order[i] = k - 1;
		}
		scanf("%s", word);
		for(i = 0; word[i] != 0; ++i) {
			terminal[i] = word[i] - '0';
		}
		len = i;
		// printf("%d %s\n", len, word);
		scanf("%d", &num);
		printf("S-Tree #%d:\n", j);
		while(num--) {
			scanf("%s", word);
			lent = len;
			it = 0;
			for(i = 0; i < n; ++i) {
				k = word[order[i]] - '0';
				if(k == 1) {
					it += lent / 2;
				} else {
					// it -= lent / 2;
				}
				lent /= 2;
			}
			// printf("[%d %d] ", it, terminal[it]);
			printf("%d", terminal[it]);
		}
		printf("\n\n");
	}
	return 0;
}

