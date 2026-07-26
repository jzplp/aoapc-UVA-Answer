#include <stdio.h>
#include <string.h>
#define MAXN 505

int arr[MAXN];
int arrV[MAXN];
int m, k;
long long sum, max;

bool getSum(long long v)
{
  int ki = k;
  int i, j;
  long long sumt = 0;
  for (i = 0; i < m; ++i)
  {
    sumt += arr[i];
    if (sumt > v)
    {
      --ki;
      sumt = arr[i];
    }
    if (ki <= 0)
      return false;
  }
  return true;
}

long long computed(long long beg, long long end)
{
  long long mid = (beg + end) / 2;
  if (mid == beg)
  {
    if (getSum(mid))
      return mid;
    return end;
  }
  if (getSum(mid))
    end = mid;
  else
    beg = mid;
  return computed(beg, end);
}

void getPrint(long long v)
{
  int i, j, ki = k - 1;
  long long sumt = 0;
  for (i = m - 1; i >= 0; --i)
  {
    if (i <= ki)
    {
      if (sumt + arr[i] > v)
      {
        --ki;
        arrV[i] = ki;
        sumt = arr[i];
        continue;
      }
      arrV[i] = ki--;
      sumt = 0;
      continue;
    }
    sumt += arr[i];
    arrV[i] = ki;
    if (sumt > v)
    {
      --ki;
      sumt = arr[i];
      arrV[i] = ki;
    }
  }
}

int main()
{
  int i, j, N;
  long long v;
  scanf("%d", &N);
  while (N--)
  {
    sum = 0;
    max = 0;
    scanf("%d %d", &m, &k);
    for (i = 0; i < m; ++i)
    {
      scanf("%d", &arr[i]);
      sum += arr[i];
      if (arr[i] > max)
        max = arr[i];
    }
    v = computed(max, sum);
    getPrint(v);
    for (i = 0; i < m; ++i)
    {
      printf("%d", arr[i]);
      if (i + 1 != m)
      {
        printf(" ");
        if (arrV[i + 1] != arrV[i])
          printf("/ ");
      }
    }
    putchar('\n');
  }
  return 0;
}
