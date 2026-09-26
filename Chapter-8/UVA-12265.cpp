#include <stdio.h>
#include <map>
#include <list>
#define MAXMN 1005

using namespace std;

int arr[MAXMN][MAXMN];
int m, n;
// 当前格往上的连续最高格
int arrTop[MAXMN][MAXMN];
// 存放结果数据
map<int, int> mp;

void outputArr()
{
  int i, j;
  for (i = 0; i < m; ++i)
  {
    for (j = 0; j < n; ++j)
      printf("%d", arrTop[i][j]);
    putchar('\n');
  }
  putchar('\n');
}

void getArrTop()
{
  int i, j;
  for (i = 0; i < n; ++i)
  {
    arrTop[0][i] = arr[0][i];
    for (j = 1; j < m; ++j)
    {
      if (arr[j][i] == 0)
        arrTop[j][i] = 0;
      else
        arrTop[j][i] = arrTop[j - 1][i] + 1;
    }
  }
}

struct Node
{
  int num, top;
};

void printList(list<Node> &ls)
{
  for (auto ip = ls.begin(); ip != ls.end(); ++ip)
  {
    printf("top %d num %d\n", ip->top, ip->num);
  }
}

void computed(int line)
{
  int i, j, maxV, value;
  list<Node> ls;
  auto ip = ls.begin(), ipt = ls.begin();
  for (i = 0; i < n; ++i)
  {
    if (arr[line][i] == 0) {
      // 清空list
      ls.clear();
      continue;
    }
    Node no = {i, arrTop[line][i]};
    ls.push_back(no);
    // 统一调整限高
    for (ip = ls.begin(); ip != ls.end(); ++ip)
    {
      if (ip->top > no.top)
        ip->top = no.top;
    }
    // 统一计算去掉的情况
    ip = ls.begin(), ipt = ls.begin();
    ++ip;
    while (ip != ls.end())
    {
      if (ip->top <= ipt->top)
      {
        ip = ls.erase(ip);
      }
      else
      {
        ipt = ip;
        ++ip;
      }
    }
    // 统一计算最大值
    maxV = 0;
    for (ip = ls.begin(); ip != ls.end(); ++ip)
    {
      value = ip->top * 2 + 2 * (i - ip->num + 1);
      if (maxV < value)
        maxV = value;
    }
    if (maxV != 0)
    {
      if (!mp[maxV])
        mp[maxV] = 1;
      else
        mp[maxV]++;
    }
  }
}

int main()
{
  int t;
  int i, j;
  char c;
  scanf("%d", &t);
  while (t--)
  {
    scanf("%d %d", &m, &n);
    for (i = 0; i < m; ++i)
    {
      getchar();
      for (j = 0; j < n; ++j)
      {
        scanf("%c", &c);
        if (c == '.')
          arr[i][j] = 1;
        else
          arr[i][j] = 0;
      }
    }
    getArrTop();
    mp.clear();
    for (i = 0; i < m; ++i)
      computed(i);
    for (auto ip = mp.begin(); ip != mp.end(); ++ip)
    {
      printf("%d x %d\n", ip->second, ip->first);
    }
  }

  return 0;
}