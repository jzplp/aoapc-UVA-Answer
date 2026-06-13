#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MIN_DIFF 10e-9

struct Item
{
  int x, y;
  int t;
  double angle;
};

// 原始数据
Item arrOrigin[1010];
int n;

Item arr[1010];

int compare(const void *left, const void *right)
{
  if (((const Item *)left)->angle > ((const Item *)right)->angle)
    return 1;
  if (((const Item *)left)->angle < ((const Item *)right)->angle)
    return -1;
  return 0;
}

bool getEqualAngle(double angle1, double angle2)
{
  return abs(fmod(angle1 - angle2 + 2 * M_PI, 2 * M_PI)) < MIN_DIFF;
}

// 预处理，变为以a点做起点
void preI(int a)
{
  int i, j = 0;
  int x = arrOrigin[a].x, y = arrOrigin[a].y;
  for (i = 0; i < n; ++i)
  {
    if (i == a) // 去掉原点本身
      continue;
    // 以第a个点为零点转换坐标系
    arr[j].x = arrOrigin[i].x - x;
    arr[j].y = arrOrigin[i].y - y;
    arr[j].t = arrOrigin[i].t;
    // 求atan2角度，最小角度0
    arr[j].angle = fmod(atan2(arr[j].y, arr[j].x) + 2 * M_PI, 2 * M_PI);
    ++j;
  }
  // 从小到大排序
  qsort(arr, n - 1, sizeof(Item), compare);
}

int getRes(int topWhite, int topBlack, int bottomWhite, int bottomBlack, int line)
{
  int res1 = topWhite + bottomBlack;
  int res2 = topBlack + bottomWhite;
  return (res1 > res2 ? res1 : res2) + 1 + line;
}

// 计算
int computedI()
{
  int i, j, i1 = 0, i2 = 0, j1 = 0, j2 = 0, ii, jj;
  bool flag = false;
  double ai, aj, a;
  int topWhite = 0, topBlack = 0, bottomWhite = 0, bottomBlack = 0, lineLeftWhite = 0, lineLeftBlack = 0, lineRightWhite = 0, lineRightBlack = 0;
  int maxRes = 0, res;
  // 计算起始个数
  // 计算0-180度的数量（不含180）
  for (i = 0; i < n - 1; ++i)
  {
    if (arr[i].angle < MIN_DIFF)
    {
      if (arr[i].t)
        ++lineLeftWhite;
      else
        ++lineLeftBlack;
      continue;
    }
    if (abs(arr[i].angle - M_PI) < MIN_DIFF || arr[i].angle > M_PI)
      break;
    if (arr[i].t)
      ++topWhite;
    else
      ++topBlack;
  }

  i1 = lineLeftWhite + lineLeftBlack;
  i2 = i;
  // 计算180-360度的数量（含180）
  for (; i < n - 1; ++i)
  {
    if (abs(arr[i].angle - M_PI) < MIN_DIFF)
    {
      if (arr[i].t)
        ++lineRightWhite;
      else
        ++lineRightBlack;
      j1 = i + 1;
      continue;
    }
    if (abs(arr[i].angle - 2 * M_PI) < MIN_DIFF)
    {
      if (!flag)
      {
        j2 = i;
        flag = true;
      }
      if (arr[i].t)
        ++lineLeftWhite;
      else
        ++lineLeftBlack;
      continue;
    }
    if (arr[i].t)
      ++bottomWhite;
    else
      ++bottomBlack;
  }
  maxRes = getRes(topWhite, topBlack, bottomWhite, bottomBlack, lineLeftWhite + lineLeftBlack + lineRightWhite + lineRightBlack);

  // 准备工作结束，开始遍历
  i = i1;
  j = j1 ? j1 : i2;
  j2 = flag ? j2 : (n - 1);
  while (i < i2 && j < j2)
  {
    topWhite += lineRightWhite;
    topBlack += lineRightBlack;
    bottomWhite += lineLeftWhite;
    bottomBlack += lineLeftBlack;
    lineRightWhite = 0;
    lineRightBlack = 0;
    lineLeftWhite = 0;
    lineLeftBlack = 0;
    ai = arr[i].angle;
    aj = arr[j].angle;
    if (ai + M_PI < aj)
      a = ai;
    else
      a = aj - M_PI;
    ii = i;
    jj = j;
    while (abs(arr[ii].angle - a) < MIN_DIFF && ii < i2)
    {
      if (arr[ii].t)
      {
        ++lineLeftWhite;
        --topWhite;
      }
      else
      {
        ++lineLeftBlack;
        --topBlack;
      }
      ++ii;
    }
    while (abs(arr[jj].angle - a - M_PI) < MIN_DIFF && jj < j2)
    {
      if (arr[jj].t)
      {
        ++lineRightWhite;
        --bottomWhite;
      }
      else
      {
        ++lineRightBlack;
        --bottomBlack;
      }
      ++jj;
    }
    i = ii;
    j = jj;
    res = getRes(topWhite, topBlack, bottomWhite, bottomBlack, lineLeftWhite + lineLeftBlack + lineRightWhite + lineRightBlack);
    if (res > maxRes)
      maxRes = res;
  }
  while (i < i2)
  {
    topWhite += lineRightWhite;
    topBlack += lineRightBlack;
    bottomWhite += lineLeftWhite;
    bottomBlack += lineLeftBlack;
    lineRightWhite = 0;
    lineRightBlack = 0;
    lineLeftWhite = 0;
    lineLeftBlack = 0;
    ii = i;
    a = arr[i].angle;
    while (abs(arr[ii].angle - a) < MIN_DIFF && ii < i2)
    {
      if (arr[ii].t)
      {
        ++lineLeftWhite;
        --topWhite;
      }
      else
      {
        ++lineLeftBlack;
        --topBlack;
      }
      ++ii;
    }
    i = ii;
    res = getRes(topWhite, topBlack, bottomWhite, bottomBlack, lineLeftWhite + lineLeftBlack + lineRightWhite + lineRightBlack);
    if (res > maxRes)
      maxRes = res;
  }
  while (j < j2)
  {
    topWhite += lineRightWhite;
    topBlack += lineRightBlack;
    bottomWhite += lineLeftWhite;
    bottomBlack += lineLeftBlack;
    lineRightWhite = 0;
    lineRightBlack = 0;
    lineLeftWhite = 0;
    lineLeftBlack = 0;
    jj = j;
    a = arr[j].angle;
    while (abs(arr[jj].angle - a) < MIN_DIFF && jj < j2)
    {
      if (arr[jj].t)
      {
        ++lineRightWhite;
        --bottomWhite;
      }
      else
      {
        ++lineRightBlack;
        --bottomBlack;
      }
      ++jj;
    }
    j = jj;
    res = getRes(topWhite, topBlack, bottomWhite, bottomBlack, lineLeftWhite + lineLeftBlack + lineRightWhite + lineRightBlack);
    if (res > maxRes)
      maxRes = res;
  }
  return maxRes;
}

int computed()
{
  int i, j, k;
  int maxRes = 0, res;
  for (i = 0; i < n; ++i)
  {
    preI(i);
    res = computedI();
    if (res > maxRes)
      maxRes = res;
  }
  return maxRes;
}

int main()
{
  int i, j;
  while (scanf("%d", &n) > 0 && n > 0)
  {
    for (i = 0; i < n; ++i)
      scanf("%d %d %d", &arrOrigin[i].x, &arrOrigin[i].y, &arrOrigin[i].t);
    printf("%d\n", computed());
  }
  return 0;
}