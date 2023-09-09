#include<stdio.h>
 
int n, s1, v1, s2, v2;
 
long long getCount(int num, int type) {
	long long sumV = 0, maxV = 0;
	for(int i = 0; i <= num; ++i) {
		if(type == 1) {
			if((n - i * s1) < 0) continue;
			sumV = (long long)i * v1 + ((long long)(n - i * s1) / s2) * v2;
		} else {
			if((n - i * s2) < 0) continue;
			sumV = (long long)i * v2 + ((long long)(n - i * s2) / s1) * v1;
		}
		// printf("%lld %lld\n", sumV, maxV);
		if(sumV > maxV) maxV = sumV;
	}
	return maxV;
}
 
 
long long getRes() {
	int a = n / s1;
	int b = n / s2;
	int type;
	if ((long long)s2 * v1 > (long long)s1 * v2) {
		type = 2; 
	} else if((long long)s2 * v1 < (long long)s1 * v2) {
		type = 1;
	} else {
		if(s1 > s2) {
			type = 1;
		} else {
			type = 2; 
		} 
	}
	int typeNum = type == 1 ? s2 : s1;
	// printf("%d %d %d %d\n", a, b, type, typeNum);
	if(a <= b && a <= typeNum) {
		return getCount(a, 1);
	}
	else if(b <= a && b <= typeNum) {
		return getCount(b, 2);
	}
	else if(typeNum <= a && typeNum <= b) {
		return getCount(typeNum, type);
	}
	return getCount(a, 1);
}
 
int main() {
	int t, ti = 0;
	scanf("%d", &t);
	while(ti++ != t) {
		scanf("%d %d %d %d %d", &n, &s1, &v1, &s2, &v2);
		// printf("%d\n", n);
		printf("Case #%d: %lld\n", ti, getRes());
	}
	return 0; 
} 
