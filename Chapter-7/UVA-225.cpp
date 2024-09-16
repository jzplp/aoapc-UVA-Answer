#include <stdio.h>
#include <string.h>
#define LINENUMMAX 22
#define MAXBLOCKNUM 51

int lineNumMax;
// 当前的
int line[LINENUMMAX];
// 全部的
int totalNum;
int lintTotal[5000][LINENUMMAX];
// 已访问过的块
int map[500][500];

// 序号从 1 开始
// n上 s下 e右 w左
// 数字 到 字母 字典序
char num2str[5] = {0, 'e', 'n', 's', 'w'};
// 方向对应的坐标移动
char steps[5][2] = {{}, {1, 0}, {0, 1}, {0, -1}, {-1, 0}};
// 方向对应的转90度方向
int truns[5][2] = {{}, {2, 3}, {1, 4}, {1, 4}, {2, 3}};

void init()
{
  int i, x, y, n;
  scanf("%d", &lineNumMax);
  scanf("%d", &n);
  memset(map, 0, sizeof(map));
  memset(line, 0, sizeof(line));
  memset(lintTotal, 0, sizeof(lintTotal));
  for (i = 0; i < n; ++i)
  {
    scanf("%d %d", &x, &y);
    map[x + 250][y + 250] = 2;
  }
  totalNum = 0;
}

// 判断向当前方向走，会不会碰到阻碍 注意这里是移动之前判断
// n 当前长度 i 上一次方向 x,y 当前坐标 xnew ynew 新坐标
bool hasBlock(int i, int x, int y, int xnew, int ynew)
{
  int a;
  if (i == 1)
  {
    for (a = x + 1; a <= xnew; ++a)
      if (map[a + 250][y + 250] == 2)
        return true;
  }
  if (i == 2)
  {
    for (a = y + 1; a <= ynew; ++a)
      if (map[x + 250][a + 250] == 2)
        return true;
  }
  if (i == 3)
  {
    for (a = ynew; a < y; ++a)
      if (map[x + 250][a + 250] == 2)
        return true;
  }
  if (i == 4)
  {
    for (a = xnew; a < x; ++a)
      if (map[a + 250][y + 250] == 2)
        return true;
  }
  return false;
}

// n 当前长度 i 上一次方向 x,y 当前坐标
void dfs(int n, int i, int x, int y)
{
  int a, newi, xnew, ynew;
  if (x == 0 && y == 0 && n == lineNumMax)
  {
    for (a = 0; a < lineNumMax; ++a)
      lintTotal[totalNum][a] = line[a];
    totalNum++;
    return;
  }
  if (n >= lineNumMax)
    return;
  map[x + 250][y + 250] = 1;
  for (a = 0; a < 2; ++a)
  {
    newi = truns[i][a];
    xnew = x + (n + 1) * steps[newi][0];
    ynew = y + (n + 1) * steps[newi][1];
    if (map[xnew + 250][ynew + 250] || hasBlock(newi, x, y, xnew, ynew))
      continue;
    line[n] = newi;
    dfs(n + 1, newi, xnew, ynew);
  }
  map[x + 250][y + 250] = 0;
}

void computed()
{
  int i, j;
  int x, y;
  // 四个方向都走一遍
  for (i = 1; i < 5; ++i)
  {
    line[0] = i;
    x = steps[i][0];
    y = steps[i][1];
    if (map[x + 250][y + 250])
      continue;
    dfs(1, i, x, y);
  }
}

int main()
{
  int co, i, j;
  scanf("%d", &co);
  while (co--)
  {
    init();
    computed();
    for (i = 0; i < totalNum; ++i)
    {
      for (j = 0; j < lineNumMax; ++j)
        printf("%c", num2str[lintTotal[i][j]]);
      putchar('\n');
    }
    printf("Found %d golygon(s).\n\n", totalNum);
  }
  return 0;
}