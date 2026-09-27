#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>

using namespace std;

map<int, int> mp;
int n, l;

void reduce(int i)
{
  if (mp[i] > 1)
    mp[i]--;
  else
    mp.erase(i);
}

int computed()
{
  int num = 0;
  int i, j;
  auto ip = mp.end(), jp = mp.end();
  while (!mp.empty())
  {
    ++num;
    // 找出当前最大的元素
    ip = mp.end();
    ip--;
    i = ip->first;
    reduce(i);
    // 尝试找出适配的元素
    if (l == i)
      continue;
    if (mp.empty())
      break;
    ip = mp.upper_bound(l - i);
    if (ip == mp.begin())
      continue;
    --ip;
    reduce(ip->first);
  }

  return num;
}

int main()
{
  int t, i, j, k;
  scanf("%d", &t);
  while (t--)
  {
    scanf("%d %d", &n, &l);
    mp.clear();
    for (i = 0; i < n; ++i)
    {
      scanf("%d", &j);
      if (!mp[j])
        mp[j] = 1;
      else
        mp[j] += 1;
    }
    printf("%d\n", computed());
    if (t != 0)
      putchar('\n');
  }
  return 0;
}