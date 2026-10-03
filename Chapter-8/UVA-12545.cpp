#include <stdio.h>
#include <stdlib.h>
#define MAXN 105

char sArr[MAXN];
char tArr[MAXN];
int n;
int sZeroNum, sOneNum, sQuesNum;
int tZeroNum, tOneNum;

int judge()
{
  int i;
  sZeroNum = 0;
  sOneNum = 0;
  sQuesNum = 0;
  tZeroNum = 0;
  tOneNum = 0;
  for (n = 0; tArr[n] != 0; ++n)
  {
    if (tArr[n] == '0')
      ++tZeroNum;
    if (tArr[n] == '1')
      ++tOneNum;
  }
  for (i = 0; i < n; ++i)
  {
    if (sArr[i] == '0')
      ++sZeroNum;
    if (sArr[i] == '1')
      ++sOneNum;
    if (sArr[i] == '?')
      ++sQuesNum;
  }
  if (tZeroNum > sZeroNum + sQuesNum)
    return false;
  return true;
}

int computed()
{
  int num = 0;
  int i, j, k;
  // 所有问号对应0的位置先赋值
  for (i = 0; i < n; ++i)
  {
    if (sArr[i] != '?')
      continue;
    if (tArr[i] == '0')
    {
      sArr[i] = '0';
      sQuesNum--;
      sZeroNum++;
      ++num;
    }
  }
  // 如果0依然不够，那就从1的位置补齐
  for (i = 0; i < n; ++i)
  {
    if (sArr[i] != '?')
      continue;
    if (sZeroNum < tZeroNum)
    {
      sArr[i] = '0';
      ++sZeroNum;
    }
    else
    {
      sArr[i] = '1';
      ++sOneNum;
    }
    ++num;
  }
  // 找出两者的不同的点，如果是0-1和0-1的不同可以交换，剩下的不同则只能变换
  j = 0;
  k = 0;
  for (i = 0; i < n; ++i)
  {
    if (sArr[i] == '0' && tArr[i] == '1')
      ++j;
    if (sArr[i] == '1' && tArr[i] == '0')
      ++k;
  }
  num += j > k ? j : k;
  return num;
}

int main()
{
  int t, i;
  scanf("%d", &t);
  for (int ti = 0; ti < t; ++ti)
  {
    scanf("%s", sArr);
    scanf("%s", tArr);
    printf("Case %d: ", ti + 1);
    if (!judge())
    {
      printf("-1\n");
      continue;
    }
    printf("%d\n", computed());
  }
  return 0;
}