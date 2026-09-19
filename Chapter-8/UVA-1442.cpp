#include <stdio.h>
#define MAXN 1000005

int arrFloor[MAXN];   // 地板
int arrCeiling[MAXN]; // 天花板
int arrValue[MAXN];   // 当前水位
int n;

void computedFront()
{
  int i;
  arrValue[0] = arrCeiling[0];
  for (i = 1; i < n; ++i)
  {
    if (arrCeiling[i] <= arrFloor[i - 1])
    {
      arrValue[i] = arrCeiling[i];
      continue;
    }
    if (arrCeiling[i] >= arrFloor[i - 1] && arrCeiling[i] <= arrCeiling[i - 1] && arrFloor[i] <= arrFloor[i - 1])
    {
      if (arrCeiling[i] <= arrValue[i - 1])
        arrValue[i] = arrCeiling[i];
      else
        arrValue[i] = arrValue[i - 1];
      continue;
    }
    if (arrCeiling[i] <= arrCeiling[i - 1] && arrFloor[i] >= arrFloor[i - 1])
    {
      if (arrCeiling[i] <= arrValue[i - 1])
        arrValue[i] = arrCeiling[i];
      else if (arrFloor[i] <= arrValue[i - 1])
        arrValue[i] = arrValue[i - 1];
      else
        arrValue[i] = arrFloor[i];
      continue;
    }
    if (arrCeiling[i] >= arrCeiling[i - 1] && arrFloor[i] >= arrFloor[i - 1] && arrFloor[i] <= arrCeiling[i - 1])
    {
      if (arrFloor[i] <= arrValue[i - 1])
        arrValue[i] = arrValue[i - 1];
      else
        arrValue[i] = arrFloor[i];
      continue;
    }
    if (arrFloor[i] >= arrCeiling[i - 1])
    {
      arrValue[i] = arrFloor[i];
      continue;
    }
    if (arrFloor[i] <= arrFloor[i - 1] && arrCeiling[i] >= arrCeiling[i - 1])
    {
      if (arrFloor[i] <= arrValue[i - 1])
        arrValue[i] = arrValue[i - 1];
      else
        arrValue[i] = arrFloor[i];
      continue;
    }
    // arrValue[i] = arrValue[i - 1];
  }
}

void computedBack()
{
  int i;
  for (i = n - 2; i >= 0; --i)
  {
    if (arrCeiling[i] <= arrFloor[i + 1])
      continue;
    if (arrCeiling[i] >= arrFloor[i + 1] && arrCeiling[i] <= arrCeiling[i + 1] && arrFloor[i] <= arrFloor[i + 1])
    {
      if (arrValue[i + 1] <= arrValue[i])
        arrValue[i] = arrValue[i + 1];
      continue;
    }
    if (arrCeiling[i] <= arrCeiling[i + 1] && arrFloor[i] >= arrFloor[i + 1])
    {
      if (arrValue[i + 1] <= arrValue[i])
        arrValue[i] = arrValue[i + 1] > arrFloor[i] ? arrValue[i + 1] : arrFloor[i];
      continue;
    }
    if (arrCeiling[i] >= arrCeiling[i + 1] && arrFloor[i] >= arrFloor[i + 1] && arrFloor[i] <= arrCeiling[i + 1])
    {
      if (arrValue[i + 1] <= arrValue[i])
        arrValue[i] = arrValue[i + 1] > arrFloor[i] ? arrValue[i + 1] : arrFloor[i];
      continue;
    }
    if (arrFloor[i] >= arrCeiling[i + 1])
    {
      arrValue[i] = arrFloor[i];
      continue;
    }
    if (arrFloor[i] <= arrFloor[i + 1] && arrCeiling[i] >= arrCeiling[i + 1])
    {
      if (arrValue[i + 1] <= arrValue[i])
        arrValue[i] = arrValue[i + 1];
      continue;
    }
  }
}

int main()
{
  int z, i;
  long long sum;
  scanf("%d", &z);
  while (z--)
  {
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
      scanf("%d", &arrFloor[i]);
    for (i = 0; i < n; ++i)
      scanf("%d", &arrCeiling[i]);
    computedFront();
    computedBack();
    sum = 0;
    for (i = 0; i < n; ++i)
    {
      sum += arrValue[i] - arrFloor[i];
    }
    printf("%lld\n", sum);
  }

  return 0;
}