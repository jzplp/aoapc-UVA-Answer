#include <stdio.h>
#include <stdlib.h>

int arr[4][4100];
int n;
int count = 0;
int addArr[17000000];

int compare(const void *left, const void *right)
{
  return *(int *)left - *(int *)right;
}

int lowerBound(int num)
{
  int beg = 0, end = n * n, mid;
  while (end > beg)
  {
    mid = beg + (end - beg) / 2;
    if (addArr[mid] >= num)
      end = mid;
    if (addArr[mid] < num)
      beg = mid + 1;
  }
  return beg;
}

int upperBound(int num)
{
  int beg = 0, end = n * n, mid;
  while (end > beg)
  {
    mid = beg + (end - beg) / 2;
    if (addArr[mid] > num)
      end = mid;
    if (addArr[mid] <= num)
      beg = mid + 1;
  }
  return beg;
}

void computed()
{
  int i, j, sum, upper, lower;
  for (i = 0; i < n; ++i)
  {
    for (j = 0; j < n; ++j)
      addArr[i * n + j] = arr[0][i] + arr[1][j];
  }
  qsort(addArr, n * n, sizeof(int), compare);
  for (i = 0; i < n; ++i)
  {
    for (j = 0; j < n; ++j)
    {
      sum = arr[2][i] + arr[3][j];
      upper = upperBound(-sum);
      lower = lowerBound(-sum);
      count += upper - lower;
    }
  }
}

int main()
{
  int t, i, j;
  scanf("%d", &t);
  while (t--)
  {
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
    {
      for (j = 0; j < 4; ++j)
        scanf("%d", &arr[j][i]);
    }
    count = 0;
    computed();
    printf("%d\n", count);
    if (t != 0)
      putchar('\n');
  }
}