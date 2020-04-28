#include<algorithm>
#include<cstdio>
using namespace std;

int arr1[30], arr2[30];
char s1[105];

int main() {
	int i;
	while(scanf("%s", s1) == 1) {
		for(i=0; i<26; ++i) {
			arr1[i] = 0;
			arr2[i] = 0;
		}
		for(i=0; s1[i]!=0; ++i)
			arr1[s1[i]-'A']++;
		scanf("%s", s1);
		for(i=0; s1[i]!=0; ++i)
			arr2[s1[i]-'A']++;
		sort(arr1, arr1+26);
		sort(arr2, arr2+26);
		for(i=0; i<26; ++i)
			if(arr1[i] != arr2[i])
				break;
		if(i != 26)
			puts("NO");
		else
			puts("YES");
	}
	return 0;
}
