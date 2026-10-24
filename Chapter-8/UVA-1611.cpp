#include <stdio.h>
#include <string.h>
#define MAXN 10005

int n;
// 当前排列
int arr[MAXN];
// 当前排列对应的序号
int arrIndex[MAXN];
int stepNum;
int stepArr[MAXN * 2][2];

void flip(int i, int j)
{
  int t;
  if (i >= j)
  {
    printf("ERROR %d %d\n", i, j);
    return;
  }
  int len = (j - i + 1) / 2;
  for (int a = 0; a < len; ++a)
  {
    t = arr[i + a];
    arr[i + a] = arr[i + len + a];
    arr[i + len + a] = t;
    arrIndex[arr[i + a]] = i + a;
    arrIndex[arr[i + len + a]] = i + len + a;
  }
  stepArr[stepNum][0] = i;
  stepArr[stepNum][1] = j;
  ++stepNum;
}

void printArr()
{
  int i;
  for (i = 1; i <= n; ++i)
    printf("%d ", arr[i]);
  putchar('\n');
  for (i = 1; i <= n; ++i)
    printf("%d ", arrIndex[i]);
  putchar('\n');
}

void computed()
{
  int i, j, k;
  stepNum = 0;
  for (i = 1; i <= n; ++i)
  {
    if (arr[i] == i)
      continue;
    j = arrIndex[i];
    if (j == i + 1)
    {
      flip(i, j);
      continue;
    }
    k = j - i + 1;
    if (k + j - 2 <= n)
    {
      flip(i, j + k - 2);
      continue;
    }
    if (k % 2 == 0)
    {
      flip(i, j);
      flip(i, i + k - 2 - 1);
    }
    else
    {
      flip(i + 1, j);
      flip(i, j - 1);
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
    for (i = 1; i <= n; ++i)
    {
      scanf("%d", &arr[i]);
      arrIndex[arr[i]] = i;
    }
    computed();
    printf("%d\n", stepNum);
    for (i = 0; i < stepNum; ++i)
      printf("%d %d\n", stepArr[i][0], stepArr[i][1]);
  }
  return 0;
}