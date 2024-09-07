#include <stdio.h>
#include <string.h>
#define MAX 21

int terminal;
int map[MAX][MAX];
int tempLine[MAX];
int totalLine[MAX][10000];
int totalNum = 0;
int findStatus[MAX];

void copyLine(int *arr1, int *arr2)
{
  for (int i = 0; arr1[i]; ++i)
  {
    arr2[i] = arr1[i];
  }
}

// 初始化
void init()
{
  memset(map, 0, sizeof(map));
  memset(tempLine, 0, sizeof(tempLine));
  memset(totalLine, 0, sizeof(totalLine));
  memset(findStatus, 0, sizeof(findStatus));
  totalNum = 0;
}

void dfs(int i, int num)
{
  tempLine[num] = i;
  findStatus[i] = 1;
  ++num;
  if (i == terminal)
  {
    copyLine(tempLine, totalLine[totalNum]);
    ++totalNum;
    findStatus[i] = 0;
    return;
  }

  int x, y;
  for (x = 1; x < MAX; ++x)
  {
    if (map[i][x] && !findStatus[x])
    {
      dfs(x, num);
      tempLine[num] = 0;
    }
  }
  findStatus[i] = 0;
}

void findDfs(int i)
{
  findStatus[i] = 1;
  for (int x = 1; x < MAX; ++x)
  {
    if (map[i][x] && !findStatus[x])
      findDfs(x);
  }
}

int main()
{
  int x, y, i = 0;
  while (scanf("%d", &terminal) == 1)
  {
    // 初始化
    init();
    ++i;
    while (scanf("%d %d", &x, &y) == 2 && x != 0)
    {
      map[x][y] = 1;
      map[y][x] = 1;
    }
    printf("CASE %d:\n", i);
    // 先求联通图
    findDfs(1);
    if (!findStatus[terminal])
    {
      printf("There are 0 routes from the firestation to streetcorner %d.\n", terminal);
      continue;
    }
    memset(findStatus, 0, sizeof(findStatus));
    dfs(1, 0);
    for (x = 0; x < totalNum; ++x)
    {
      for (y = 0; totalLine[x][y]; ++y)
      {
        if (y != 0)
          putchar(' ');
        printf("%d", totalLine[x][y]);
      }
      putchar('\n');
    }
    printf("There are %d routes from the firestation to streetcorner %d.\n", totalNum, terminal);
  }

  return 0;
}