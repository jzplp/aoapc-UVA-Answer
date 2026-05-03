#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int n;

struct Rect
{
  int xl, yl, xr, yr;
  int num;
  int x, y;
};
Rect arr[5500];
int arrMap[5500];

int compareX(const void *left, const void *right)
{
  const Rect *l = (const Rect *)left;
  const Rect *r = (const Rect *)right;
  if (l->xr != r->xr)
  {
    return l->xr - r->xr;
  }
  return l->xl - r->xl;
}

bool computedX()
{
  int i, j;
  int flag = 0;
  qsort(arr, n, sizeof(Rect), compareX);
  memset(arrMap, 0, sizeof(arrMap));
  for (i = 0; i < n; ++i)
  {
    flag = 0;
    for (j = arr[i].xl; j <= arr[i].xr; ++j)
    {
      if (!arrMap[j])
      {
        arr[i].x = j;
        flag = 1;
        arrMap[j] = 1;
        break;
      }
    }
    if (flag == 0)
      return false;
  }
  return true;
}

int compareY(const void *left, const void *right)
{
  const Rect *l = (const Rect *)left;
  const Rect *r = (const Rect *)right;
  if (l->yr != r->yr)
  {
    return l->yr - r->yr;
  }
  return l->yl - r->yl;
}

bool computedY()
{
  int i, j;
  int flag = 0;
  qsort(arr, n, sizeof(Rect), compareY);
  memset(arrMap, 0, sizeof(arrMap));
  for (i = 0; i < n; ++i)
  {
    flag = 0;
    for (j = arr[i].yl; j <= arr[i].yr; ++j)
    {
      if (!arrMap[j])
      {
        arr[i].y = j;
        flag = 1;
        arrMap[j] = 1;
        break;
      }
    }
    if (flag == 0)
      return false;
  }
  return true;
}

int compareIndex(const void *left, const void *right)
{
  const Rect *l = (const Rect *)left;
  const Rect *r = (const Rect *)right;
  return l->num - r->num;
}

int main()
{
  int xl, yl, xr, yr, i, j;
  while (scanf("%d", &n) > 0 && n > 0)
  {
    memset(arr, 0, sizeof(arr));
    for (i = 0; i < n; ++i)
    {
      scanf("%d %d %d %d", &xl, &yl, &xr, &yr);
      arr[i] = {xl - 1, yl - 1, xr - 1, yr - 1, i, -1, -1};
    }
    if (!computedX() || !computedY())
    {
      printf("IMPOSSIBLE\n");
      continue;
    }
    qsort(arr, n, sizeof(Rect), compareIndex);
    for (i = 0; i < n; ++i)
    {
      printf("%d %d\n", arr[i].x + 1, arr[i].y + 1);
    }
  }

  return 0;
}