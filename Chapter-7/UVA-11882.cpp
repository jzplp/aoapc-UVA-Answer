#include <stdio.h>
#include <string.h>

int r, c;
int arr[32][32];
int numCount;
int findArr[32][32];
int maxNum[35];
int maxLen;
int tempNum[35];

int Steps[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

void compareMax(int len)
{
  int i, j;
  if (len > maxLen)
  {
    for (i = 0; i < len; ++i)
      maxNum[i] = tempNum[i];
    maxLen = len;
    return;
  }
  for (i = 0; i < len; ++i)
  {
    if (maxNum[i] > tempNum[i])
      return;
    if (maxNum[i] < tempNum[i])
      break;
  }
  if (i == len)
    return;
  for (i = 0; i < len; ++i)
    maxNum[i] = tempNum[i];
}

void dfs(int x, int y, int len)
{
  tempNum[len] = arr[x][y];
  findArr[x][y] = 1;
  ++len;
  int i, j, x1, y1, hasNext = 0;
  for (i = 0; i < 4; ++i)
  {
    x1 = x + Steps[i][0];
    y1 = y + Steps[i][1];
    if (x1 < 0 || x1 >= r || y1 < 0 || y1 >= c)
      continue;
    if (arr[x1][y1] == 0 || findArr[x1][y1])
      continue;
    hasNext = 1;
    dfs(x1, y1, len);
  }
  findArr[x][y] = 0;
  if (!hasNext && len >= maxLen)
    compareMax(len);
}

void computed()
{
  int i, j;
  for (i = 0; i < r; ++i)
  {
    for (j = 0; j < c; ++j)
    {
      if (arr[i][j] == 0)
        continue;
      if (numCount == maxLen && arr[i][j] < maxNum[0])
        continue;
      dfs(i, j, 0);
    }
  }
}

int main()
{
  int i, j, k;
  char ch;
  while (scanf("%d %d", &r, &c) >= 2 && r != 0 && c != 0)
  {
    memset(arr, 0, sizeof(arr));
    maxLen = 0;
    numCount = 0;
    getchar();
    for (i = 0; i < r; ++i)
    {
      for (j = 0; j < c; ++j)
      {
        ch = getchar();
        if (ch == '#')
          arr[i][j] = 0;
        else
        {
          arr[i][j] = ch - '0';
          ++numCount;
        }
      }
      getchar();
    }
    computed();
    for (i = 0; i < maxLen; ++i)
      printf("%d", maxNum[i]);
    putchar('\n');
  }
  return 0;
}
