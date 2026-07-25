#include <stdio.h>
#include <string.h>
#define MAXN 1000005

int n, l;
int arr[MAXN];
int sumArr[MAXN];

int stack[MAXN];
int stlen = 0;

struct Res
{
  int start, end;
  double value;
};

void init()
{
  int i, j;
  sumArr[0] = arr[0];
  for (i = 0; i < n; ++i)
    sumArr[i] = sumArr[i - 1] + arr[i];
  memset(stack, 0, sizeof(stack));
  /*
  for (i = 0; i < n; ++i)
    printf("%d ", sumArr[i]);
  putchar('\n');
  */
}

Res computed()
{
  int i, j, k;
  int i1, j1, j2, j3;
  double a, b = 0;
  Res resMax = {0, l - 1, (double)sumArr[l - 1] / l}, res;
  i1 = 0; // 当前切点位置 是stack的位置
  stlen = 0;
  for (i = l; i < n; ++i)
  {
    j = i - l;
    stack[stlen++] = j;
    while (stlen > 2)
    {
      j1 = stack[stlen - 1];
      j2 = stack[stlen - 2];
      j3 = stack[stlen - 3];
      if ((double)(sumArr[j2] - sumArr[j3]) / (j2 - j3) > (double)(sumArr[j1] - sumArr[j3]) / (j1 - j3))
      {
        stack[stlen - 2] = stack[stlen - 1];
        --stlen;
      }
      else
        break;
    }
    if (stlen >= 2 && i1 > stlen - 2)
      i1 = stlen - 2;
    b = 0;
    while (i1 < stlen)
    {
      a = (double)(sumArr[i] - sumArr[stack[i1]]) / (i - stack[i1]);
      if (a < b)
        break;
      b = a;
      ++i1;
    }
    i1--;
    if (resMax.value < b)
      resMax = {stack[i1] + 1, i, b};
    if (resMax.value < (double)sumArr[i] / (i + 1))
      resMax = {0, i, (double)sumArr[i] / (i + 1)};
  }
  return resMax;
}

int main()
{
  int t, i, j, k;
  char c;
  scanf("%d", &t);
  while (t--)
  {
    scanf("%d %d", &n, &l);
    getchar();
    for (i = 0; i < n; ++i)
    {
      scanf("%c", &c);
      arr[i] = c - '0';
    }
    init();
    Res res = computed();
    printf("%d %d\n", res.start + 1, res.end + 1);
  }
  return 0;
}