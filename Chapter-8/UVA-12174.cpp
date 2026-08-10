#include <stdio.h>
#include <string.h>
#define MAXN 100005

int arrn[MAXN];
int s, n;
int arrs[MAXN];
int steps[MAXN];

void computed()
{
  int wnum, step;
  int i, j, k;
  int num2 = 0;
  memset(steps, 0, sizeof(steps));
  for (wnum = 0;; ++wnum)
  {
    memset(arrs, 0, sizeof(arrs));
    // 计算初始值
    num2 = 0;
    for (i = (wnum - 1) * s - 1; i < wnum * s - 1; ++i)
    {
      if (i < 0 || i >= n)
        continue;
      arrs[arrn[i]] += 1;
      if (arrs[arrn[i]] == 2)
        ++num2;
    }
    for (step = 0; step < s; ++step)
    {
      i = step + (wnum - 1) * s;
      if (i - 1 >= n)
        return;
      // 减去前一个，增加下一个
      if (i - 1 >= 0)
      {
        if (arrs[arrn[i - 1]] == 2)
          --num2;
        arrs[arrn[i - 1]]--;
      }
      if (i + s - 1 < n)
      {
        ++arrs[arrn[i + s - 1]];
        if (arrs[arrn[i + s - 1]] == 2)
          ++num2;
      }
      if (num2 > 0)
        steps[step] = 1;
    }
  }
}

int main()
{
  int t, i, j;
  scanf("%d", &t);
  while (t--)
  {
    scanf("%d %d", &s, &n);
    for (i = 0; i < n; ++i)
      scanf("%d", &arrn[i]);
    computed();
    j = 0;
    for (i = 0; i < s; ++i)
    {
      if (steps[i] == 0)
        ++j;
    }
    printf("%d\n", j);
  }
  return 0;
}