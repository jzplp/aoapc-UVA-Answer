#include <stdio.h>
#include <string.h>
#include <list>
#define MAXN 1030

using namespace std;

int group[MAXN][MAXN];
int used[MAXN];
int n;
list<int> lsb, lsw;

int history[MAXN * MAXN][2];
int hisn;

bool judge()
{
  int i;
  for (i = 2; i <= n; ++i)
    if (!used[i])
      return false;
  return true;
}

void beat(list<int> &l1, list<int>::iterator &it, list<int> &l2, list<int>::iterator &it2)
{
  if (group[*it][*it2])
    used[*it2] = 1;
  else
    used[*it] = 1;
  history[hisn][0] = *it;
  history[hisn][1] = *it2;
  ++hisn;
  it = l1.erase(it);
  // 避免删除it2后，it也不存在了
  if (l1 == l2 && it == it2)
  {
    it2 = l2.erase(it2);
    it = it2;
  }
  else
  {
    it2 = l2.erase(it2);
  }
}

void computed()
{
  list<int>::iterator it3;
  bool flag;
  // 第一步消灭所有直接消灭的黑色
  for (auto it = lsb.begin(); it != lsb.end();)
  {
    flag = false;
    for (auto it2 = lsw.begin(); it2 != lsw.end();)
    {
      if (group[*it][*it2])
      {
        ++it2;
        continue;
      }
      beat(lsb, it, lsw, it2);
      flag = true;
      break;
    }
    if (!flag)
      ++it;
  }

  // 第二步 1和另一个
  if (lsw.size() > 0)
  {
    auto it = lsw.begin();
    used[*it] = 1;
    history[hisn][0] = 1;
    history[hisn][1] = *it;
    ++hisn;
    it = lsw.erase(it);
  }

  // 第三步 黑黑对决
  for (auto it = lsb.begin(); it != lsb.end();)
  {
    it3 = it;
    if (++it != lsb.end())
      beat(lsb, it3, lsb, it);
  }

  // 第四步 剩下混战
  for (auto it = lsw.begin(); it != lsw.end();)
  {
    it3 = it;
    if (++it != lsw.end())
      beat(lsw, it3, lsw, it);
  }
  if (lsw.size() > 0 && lsb.size() > 0)
  {
    auto it = lsb.begin(), it2 = lsw.begin();
    beat(lsw, it, lsb, it2);
  }
}

int main()
{
  int i, j;
  char c;
  while (scanf("%d", &n) > 0)
  {
    for (i = 1; i <= n; ++i)
    {
      getchar();
      for (j = 1; j <= n; ++j)
      {
        scanf("%c", &c);
        group[i][j] = c - '0';
      }
    }
    memset(used, 0, sizeof(used));
    memset(history, 0, sizeof(history));
    hisn = 0;
    while (1)
    {
      lsb.clear();
      lsw.clear();
      for (i = 2; i <= n; ++i)
      {
        if (used[i])
          continue;
        if (group[1][i])
          lsw.push_back(i);
        else
          lsb.push_back(i);
      }
      computed();
      if (judge())
        break;
    }
    for (i = 0; i < hisn; ++i)
    {
      printf("%d %d\n", history[i][0], history[i][1]);
    }
    // putchar('\n');
  }
  return 0;
}