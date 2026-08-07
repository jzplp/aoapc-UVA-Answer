#include <stdio.h>

#define MAXN 100005

int arr1[MAXN];
int arr2[MAXN];
int n;

int computed()
{
  int i = 0, j, k;
  long long sum = 0;
  bool flag;
  while (i < n)
  {
    sum = 0;
    for (j = i; j < n + i; ++j)
    {
      sum += arr1[j % n];
      sum -= arr2[j % n];
      if (sum < 0)
        break;
    }
    if (i == j)
      ++j;
    if (j == n + i)
      return i;
    if (j < n)
    {
      i = j;
      continue;
    }
    return -1;
  }
  return -1;
}

int main()
{
  int t = 0, T, i, res;
  scanf("%d", &T);
  while (T > t++)
  {
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
      scanf("%d", &arr1[i]);
    for (i = 0; i < n; ++i)
      scanf("%d", &arr2[i]);
    res = computed();
    printf("Case %d: ", t);
    if (res == -1)
      printf("Not possible\n");
    else
      printf("Possible from station %d\n", res + 1);
  }
  return 0;
}