#include <stdio.h>
#include <math.h>

long long func(int k)
{
  if (k == 0)
    return 1;
  return (long long)(pow(3, k));
}

long long fun(int k, int i)
{
  if (i == 0)
    return 0;
  if (k == 0)
    return 1;
  int half = 1 << (k - 1);
  if (i <= half)
    return 2 * fun(k - 1, i);
  return 2 * func(k - 1) + fun(k - 1, i - half);
}

int main()
{
  int t, ti, k, a, b;
  scanf("%d", &t);
  ti = 0;
  while (t--)
  {
    scanf("%d %d %d", &k, &a, &b);
    printf("Case %d: %lld\n", ++ti, fun(k, b) - fun(k, a - 1));
  }
}