#include <stdio.h>
#include <string.h>

int arr[35][35];
int n, k;

struct Group
{
  int x, y;
  int num;
  bool hasFind;
};

// 下标从1开始
Group groups[30] = {};
int glen;

bool computed(int index);

// 判断单个矩形是否符合要求
bool judgeRect(int xmin, int ymin, int xmax, int ymax)
{
  int i, j;
  for (i = xmin; i <= xmax; ++i)
  {
    for (j = ymin; j <= ymax; ++j)
    {
      if (arr[i][j])
        return false;
    }
  }
  return true;
}

// 对矩形设置值
void setRect(int xmin, int ymin, int xmax, int ymax, int v)
{
  int i, j;
  for (i = xmin; i <= xmax; ++i)
    for (j = ymin; j <= ymax; ++j)
      arr[i][j] = v;
}

int judgeTeam(int xmin, int ymin, int xmax, int ymax)
{
  int i, j;
  int index = -1;
  for (i = 1; i < glen; ++i)
  {
    if (groups[i].hasFind)
      continue;
    if (groups[i].x >= xmin && groups[i].x <= xmax && groups[i].y >= ymin && groups[i].y <= ymax)
    {
      if (index != -1)
        return -1;
      index = i;
    }
  }
  if (index == -1)
    return index;
  if (groups[index].num != (xmax - xmin + 1) * (ymax - ymin + 1))
    return -1;
  return index;
}

bool computed(int x, int y)
{
  if (x >= n)
    return true;
  if (y >= n)
    return computed(x + 1, 0);
  if (arr[x][y])
    return computed(x, y + 1);
  int i, j;
  int t;
  for (i = x; i < n; ++i)
  {
    for (j = y; j < n; ++j)
    {
      if (!judgeRect(x, y, i, j))
        continue;
      t = judgeTeam(x, y, i, j);
      if (t <= 0)
        continue;
      groups[t].hasFind = true;
      setRect(x, y, i, j, t);
      if (computed(x, y + 1))
        return true;
      setRect(x, y, i, j, 0);
      groups[t].hasFind = false;
    }
  }
  return false;
}

void output()
{
  int i, j;
  int groupMap[30] = {};
  int gi = 0;
  for (i = 0; i < n; ++i)
  {
    for (j = 0; j < n; ++j)
    {
      if (!groupMap[arr[i][j]])
        groupMap[arr[i][j]] = ++gi;

      printf("%c", groupMap[arr[i][j]] + 'A' - 1);
    }
    putchar('\n');
  }
}

int main()
{
  int i, j, kt;
  char c;
  while (scanf("%d %d", &n, &k) == 2 && n > 0 & k > 0)
  {
    memset(groups, 0, sizeof(groups));
    memset(arr, 0, sizeof(arr));
    glen = 0;
    kt = 1;
    for (i = 0; i < n; ++i)
    {
      getchar();
      for (j = 0; j < n; ++j)
      {
        c = getchar();
        if (c != '.')
        {
          groups[kt] = {i, j, c - '0', false};
          ++kt;
        }
      }
    }
    glen = kt;
    if (!computed(0, 0))
    {
      printf("xxx\n");
      continue;
    }
    output();
  }
  return 0;
}
