#include <stdio.h>
#define MAXN 305

int arr[MAXN];      // 当前数据
int arrIndex[MAXN]; // 序号，目前除了初始化后用不到
int n;
int steps[MAXN * MAXN * 2 + 5];
int sn;

void print()
{
  int i;
  for (i = 1; i <= n; ++i)
    printf("%d", arr[i]);
  putchar('\n');
}

void oper2()
{
  int i, j, a;
  a = arr[1];
  for (i = 2; i <= n; ++i)
    arr[i - 1] = arr[i];
  arr[n] = a;
  steps[sn] = 2;
  ++sn;
  // printf("1\n");
  // print();
}

void oper1()
{
  int a = arr[1];
  arr[1] = arr[2];
  arr[2] = a;
  steps[sn] = 1;
  ++sn;
  // printf("2\n");
  // print();
}

void compuetd()
{
  int i, j, k;
  for (i = n - 1; i > 0; --i)
  {
    while (arr[1] != i)
      oper2();
    while (arr[2] != i + 1)
    {
      oper1();
      oper2();
    }
  }
}

int main()
{
  int i, j;
  while (scanf("%d", &n) > 0 && n > 0)
  {
    for (i = 1; i <= n; ++i)
    {
      // 直接变为从乱排列到 1,2...,n的排列的问题
      scanf("%d", &arrIndex[i]);
      arr[arrIndex[i]] = i;
    }
    sn = 0;
    compuetd();
    for (i = 0; i < sn; ++i)
    {
      printf("%d", steps[i]);
    }
    putchar('\n');
  }
  return 0;
}