#include <stdio.h>
#include <string.h>
#define MAXN 17

// 序号从1到n
int map[MAXN][MAXN];
int n;

// 保存当前断开场景下的图
int mapTemp[MAXN][MAXN];
// 当前断开的点
int breakPoint[MAXN];
// judge中点是否访问过
int findPoint[MAXN];

void init()
{
  memset(map, 0, sizeof(map));
}

// 复制一份图
void copyMap()
{
  int i, j;
  for (i = 1; i <= n; ++i)
    for (j = 1; j <= n; ++j)
      mapTemp[i][j] = map[i][j];
}

// 由二进制数字转换为断开的点数组
int getBreakPoint(int cnt)
{
  int i, j, k = 0;
  for (i = 0; i < n; ++i)
  {
    j = (cnt / (1 << i)) % 2;
    if (j)
      ++k;
    breakPoint[i + 1] = j;
  }
  return k;
}

// 根据断开点数组来断开图
void breakMap()
{
  int i, j;
  for (i = 1; i <= n; ++i)
  {
    if (!breakPoint[i])
      continue;
    for (j = 1; j <= n; ++j)
    {
      mapTemp[i][j] = 0;
      mapTemp[j][i] = 0;
    }
  }
}

void dfs(int point)
{
  ++findPoint[point];
  for (int j = 1; j <= n; ++j)
  {
    if (!mapTemp[point][j] || j == point)
      continue;
    // 访问过的边就删掉，避免重复访问
    // 对应的，已访问过的节点可以重复访问
    mapTemp[point][j] = 0;
    mapTemp[j][point] = 0;
    dfs(j);
  }
}

// 判断有几个链，以及是否有环
int judge()
{
  // 链数 单个节点也是链
  int linkNum = 0;
  int i, j, k;

  // 首先看每个节点的度
  for (i = 1; i <= n; ++i)
  {
    k = 0;
    for (j = 1; j <= n; ++j)
      if (mapTemp[i][j])
        ++k;
    if (k > 2)
      return -1;
  }
  // 然后看每个节点是否有环
  memset(findPoint, 0, sizeof(findPoint));
  for (i = 1; i <= n; ++i)
  {
    if (findPoint[i])
      continue;
    ++linkNum;
    dfs(i);
    for (j = 1; j <= n; ++j)
    {
      if (findPoint[j] >= 2)
        return -1;
    }
  }
  return linkNum;
}

int computed()
{
  int i, j, k;
  int breakMin = n, breakNum;
  int linkNum;
  for (i = 0; i < (1 << n); ++i)
  {
    copyMap();
    breakNum = getBreakPoint(i);
    if (breakNum >= breakMin)
      continue;
    breakMap();
    linkNum = judge();
    if (linkNum < 0)
      continue;
    if (linkNum - breakNum * 2 - 1 > 0)
      continue;
    breakMin = breakNum;
  }
  return breakMin;
}

int main()
{
  int cnt = 0;
  int i, j, sum = 0;
  while (scanf("%d", &n) == 1 && n > 0)
  {
    ++cnt;
    init();
    while (scanf("%d %d", &i, &j) == 2 && i > 0)
    {
      map[i][j] = 1;
      map[j][i] = 1;
    }
    if (n > 1)
      sum = computed();
    printf("Set %d: Minimum links to open is %d\n", cnt, sum);
  }
  return 0;
}