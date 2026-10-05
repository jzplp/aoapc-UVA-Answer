#include <stdio.h>
#include <map>
#define MAXN 100005
using namespace std;

// beg 起始位置 end 终点的下一个位置
struct Stru
{
  int beg, end;
};

char s1[MAXN];
int n, d;
int s2[MAXN];
int s2len;
map<int, Stru> mp;
map<int, int> mp2;

// 调试输出
void outMap()
{
  printf("mp:\n");
  for (auto ip = mp.begin(); ip != mp.end(); ++ip)
  {
    printf("i:%d  beg:%d  end:%d \n", ip->first, ip->second.beg, ip->second.end);
  }
  printf("mp2:\n");
  for (auto ip = mp2.begin(); ip != mp2.end(); ++ip)
  {
    printf("v:%d  i:%d \n", ip->first, ip->second);
  }
  putchar('\n');
}

// 尾部所有元素一一对应
void setTail(int i)
{
  int j;
  mp2[s2len - (n - i)] = s1[i];
  for (j = i + 1; j < n; ++j)
    mp2[s2len - (n - j)] = s1[j];
}

void computed()
{
  int i, c1;
  for (i = 0; i < n; ++i)
  {
    if (mp.count(s1[i]))
    {
      if (s2len - mp[s1[i]].end <= 0)
        continue;
      if (s2len - mp[s1[i]].end >= n - i)
      {
        setTail(i);
        return;
      }
      mp[s1[i]].end = mp[s1[i]].end + 1;
      for (c1 = s1[i] - 1; c1 >= 0; --c1)
      {
        if (mp.count(c1))
          mp.erase(c1);
      }
    }
    else
    {
      for (c1 = s1[i] + 1; c1 <= 9; ++c1)
      {
        if (mp.count(c1))
        {
          if (s2len - mp[c1].end <= 0)
            break;
          if (s2len - mp[c1].end >= n - i)
          {
            setTail(i);
            return;
          }
          mp[s1[i]] = {mp[c1].end, mp[c1].end + 1};
          break;
        }
      }
      if (c1 > 9)
      {
        if (s2len >= n - i)
        {
          setTail(i);
          return;
        }
        else
          mp[s1[i]] = {0, 1};
      }
      for (c1 = s1[i] - 1; c1 >= 0; --c1)
      {
        if (mp.count(c1))
          mp.erase(c1);
      }
    }
    // printf("-- i: %d \n", i);
    // outMap();
  }
}

void outputRes()
{
  int i, j;
  for (i = 0; i < s2len; ++i)
  {
    if (mp2.count(i))
    {
      putchar(mp2[i] + '0');
      continue;
    }
    for (j = 9; j >= 0; --j)
    {
      if (!mp.count(j))
        continue;
      if (i >= mp[j].beg && i < mp[j].end)
        putchar(j + '0');
    }
  }
  putchar('\n');
}

int main()
{
  int i;
  while (scanf("%d %d", &n, &d) >= 2 && n > 0 && d > 0)
  {
    scanf("%s", s1);
    s2len = n - d;
    for (i = 0; i < n; ++i)
      s1[i] = s1[i] - '0';
    mp.clear();
    mp2.clear();
    computed();
    // outMap();
    outputRes();
  }
  return 0;
}