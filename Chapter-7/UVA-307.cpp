#include <stdio.h>
#include <stdlib.h>

int n;
int arr[100];
int max, sum;
int num;

bool judge(int t, int j)
{
  if (t == n)
    return true;
  if (arr[t] == 0 || arr[t] == num)
    return judge(t + 1, t + 2);
  int a1 = arr[t], a2 = 0;
  int i;
  for (i = j; i < n; ++i)
  {
    if (arr[i] == 0 || arr[i] + arr[t] > num)
      continue;
    if (arr[i] == a2)
      continue;
    a2 = arr[i];
    if (arr[i] + arr[t] == num)
    {
      arr[i] = 0;
      if (judge(t + 1, t + 2))
        return true;
    }
    else if (arr[i] + arr[t] < num)
    {
      arr[t] += arr[i];
      arr[i] = 0;
      if (judge(t, i + 1))
        return true;
      arr[t] = a1;
    }
    arr[i] = a2;
  }
  return false;
}

int compute()
{
  for (int i = max; i < sum / 2 + 1; ++i)
  {
    // 筛选出能整除的i
    if (sum % i)
      continue;
    num = i;
    if (!judge(0, 1))
      continue;
    return num;
  }
  return sum;
}

int compare(const void *a, const void *b)
{
  return *(int *)b - *(int *)a;
}

int main()
{
  int i;
  while (scanf("%d", &n) == 1 && n != 0)
  {
    max = 0;
    sum = 0;
    for (i = 0; i < n; ++i)
    {
      scanf("%d", &arr[i]);
      sum += arr[i];
      if (arr[i] > max)
        max = arr[i];
    }
    qsort(arr, n, sizeof(int), compare);
    printf("%d\n", compute());
  }
  return 0;
}