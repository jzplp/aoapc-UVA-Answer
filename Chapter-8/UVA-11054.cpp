#include<stdio.h>
#include<math.h>

int arr[100005];
int n;

long long computed() {
  int i;
  long long count = 0, sum = arr[0];
  for(i = 1; i < n; ++i) {
    count += abs(sum);
    sum += arr[i];
  }
  return count;
}

int main() {
  int i;
  while(scanf("%d", &n) > 0 && n > 0) {
    for(i = 0; i<n; ++i) {
      scanf("%d", &arr[i]);
    }
    printf("%lld\n", computed());
  }
  return 0;
}