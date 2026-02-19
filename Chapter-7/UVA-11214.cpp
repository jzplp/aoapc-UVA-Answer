#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

int n, m;
// 输入数据，表示需要标记的位置
int marked[12][12];
// 表示已经覆盖的位置 值表示已经覆盖的次数
int range[12][12];
int hasLine[12], hasColumn[12];

vector<int> vec;

bool judge()
{
  int i, j;
  for (i = 0; i < n; ++i)
  {
    for (j = 0; j < m; ++j)
    {
      if (!marked[i][j])
        continue;
      if (!range[i][j])
        return false;
    }
  }
  return true;
}

bool loop(int num, int a, int b)
{
  int i, j, leave, i1, i2;
  if (num == 0)
    return judge();
  if (b >= m)
  {
    a = a + 1;
    b = 0;
  }
  if (a >= n)
    return judge();
  for (i = a; i < n; ++i)
  {
    if (hasLine[i])
      continue;
    for (j = (i == a ? b : 0); j < m; ++j)
    {
      if (hasColumn[j])
        continue;
      leave = (n - i - 1) * m + m - j;
      if (leave < num)
      {
        return false;
      }
      // 在i,j处放置一个皇后
      vec.push_back(i * 100 + j);
      // 处理已经覆盖的位置
      for (i1 = 0; i1 < n; ++i1)
        range[i1][j]++;
      for (i2 = 0; i2 < m; ++i2)
        range[i][i2]++;
      for (i1 = 0; i1 < 10; ++i1)
      {
        if (i + i1 >= n || j + i1 >= m)
          break;
        range[i + i1][j + i1]++;
      }
      for (i1 = 0; i1 < 10; ++i1)
      {
        if (i + i1 >= n || j - i1 < 0)
          break;
        range[i + i1][j - i1]++;
      }
      for (i1 = 0; i1 < 10; ++i1)
      {
        if (i - i1 < 0 || j + i1 >= n)
          break;
        range[i - i1][j + i1]++;
      }
      for (i1 = 0; i1 > -10; --i1)
      {
        if (i + i1 < 0 || j + i1 < 0)
          break;
        range[i + i1][j + i1]++;
      }
      range[i][i2] -= 5;
      hasLine[i] = 1;
      hasColumn[j] = 1;

      if (loop(num - 1, i, j + 1))
        return true;

      // 恢复原状
      vec.pop_back();
      // 处理已经覆盖的位置
      for (i1 = 0; i1 < n; ++i1)
        range[i1][j]--;
      for (i2 = 0; i2 < m; ++i2)
        range[i][i2]--;
      for (i1 = 0; i1 < 10; ++i1)
      {
        if (i + i1 >= n || j + i1 >= m)
          break;
        range[i + i1][j + i1]--;
      }
      for (i1 = 0; i1 < 10; ++i1)
      {
        if (i + i1 >= n || j - i1 < 0)
          break;
        range[i + i1][j - i1]--;
      }
      for (i1 = 0; i1 < 10; ++i1)
      {
        if (i - i1 < 0 || j + i1 >= n)
          break;
        range[i - i1][j + i1]--;
      }
      for (i1 = 0; i1 > -10; --i1)
      {
        if (i + i1 < 0 || j + i1 < 0)
          break;
        range[i + i1][j + i1]--;
      }
      range[i][i2] += 5;
      hasLine[i] = 0;
      hasColumn[j] = 0;
    }
  }
  return false;
}

int main()
{
  int i, j, num = 0;
  char c;
  while (scanf("%d %d", &n, &m) == 2)
  {
    if (n == 0 || m == 0)
      return 0;
    getchar();

    memset(marked, 0, sizeof(marked));
    memset(range, 0, sizeof(range));
    memset(hasLine, 0, sizeof(hasLine));
    memset(hasColumn, 0, sizeof(hasColumn));

    for (i = 0; i < n; ++i)
    {
      for (j = 0; j < m; ++j)
      {
        scanf("%c", &c);
        if (c == 'X')
          marked[i][j] = 1;
        else
          marked[i][j] = 0;
      }
      getchar();
    }

    for (i = 0; i < 10; ++i)
    {
      if (loop(i, 0, 0))
        break;
    }
    printf("Case %d: %d\n", ++num, i);
  }

  return 0;
}