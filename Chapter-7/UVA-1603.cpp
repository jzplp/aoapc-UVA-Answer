#include <stdio.h>
#include <string.h>
#define MAX_LINE_LEN 2 * 5 * 6 + 2
#define MAX_SQUARE_LEN 5 * 5 + 4 * 4 + 3 * 3 + 2 * 2 + 1 + 2

int n;
// 每条边是否存在 范围1~lineLen  0存在，1不存在
int lineArr[MAX_LINE_LEN] = {};
// 边的个数
int lineLen = 0;

// 每个正方形是否存在 范围1~squareLen 0存在，1不存在
int arrSquare[MAX_SQUARE_LEN] = {};
// 正方形的个数
int squareLen = 0;
// 每条正方形是否对应这个边
// lineSquare[i][j] i正方形编号 j边 1对应，0不对应
int lineSquare[MAX_SQUARE_LEN][MAX_LINE_LEN] = {};
// 递归存储每个层级当前正方形是否存在
int stackSquare[MAX_SQUARE_LEN][MAX_SQUARE_LEN] = {};
// 目前找到的最小层数
int minNum = 0;

// 填充边和正方形
void fillInit(int line, int count)
{
  lineSquare[count][line] = 1;
  if (lineArr[line])
    arrSquare[count] = 1;
}

// 填充上面的初始化数据
void init()
{
  int i, j, k, x, y;
  int count = 0;
  // n种大小的正方形
  for (i = 1; i <= n; ++i)
  {
    // 横坐标
    for (x = 1; x <= n - (i - 1); ++x)
    {
      // 纵坐标
      for (y = 1; y <= n - (i - 1); ++y)
      {
        ++count;
        // 正方形上边
        j = (x - 1) * (2 * n + 1) + y;
        for (k = 0; k < i; ++k)
          fillInit(j + k, count);
        // 正方形下边
        j = (x - 1) * (2 * n + 1) + (2 * n + 1) * i + y;
        for (k = 0; k < i; ++k)
          fillInit(j + k, count);
        // 正方形左侧
        j = (x - 1) * (2 * n + 1) + n + y;
        for (k = 0; k < i; ++k)
          fillInit(j + k * (2 * n + 1), count);
        // 正方形右侧
        j = (x - 1) * (2 * n + 1) + n + y + i;
        for (k = 0; k < i; ++k)
          fillInit(j + k * (2 * n + 1), count);
      }
    }
  }
  squareLen = count;
  for (i = 1; i <= squareLen; ++i)
  {
    stackSquare[0][i] = arrSquare[i];
  }
}

bool computed(int counti)
{
  int i, j, k;
  int countMin = minNum;
  for (i = 1; i <= squareLen; ++i)
  {
    if (!stackSquare[counti][i])
      break;
  }
  if (i > squareLen)
    return true;
  if (minNum <= counti)
    return false;

  ++counti;
  for (k = 1; k <= squareLen; ++k)
    stackSquare[counti][k] = stackSquare[counti - 1][k];
  for (j = 1; j <= lineLen; ++j)
  {
    if (!lineSquare[i][j] || lineArr[j])
      continue;
    lineArr[j] = 1;
    for (k = 1; k <= squareLen; ++k)
    {
      if (lineSquare[k][j])
        stackSquare[counti][k] = 1;
    }
    if (computed(counti))
      return true;
    // 恢复
    for (k = 1; k <= squareLen; ++k)
      stackSquare[counti][k] = stackSquare[counti - 1][k];
    lineArr[j] = 0;
  }
  return false;
}

int main()
{
  int t;
  int i, j, k;
  scanf("%d", &t);
  while (t--)
  {
    scanf("%d", &n);
    scanf("%d", &j);
    if (n <= 0)
    {
      printf("0\n");
      continue;
    }
    lineLen = 2 * n * (n + 1);
    memset(lineArr, 0, sizeof(lineArr));
    memset(arrSquare, 0, sizeof(arrSquare));
    memset(lineSquare, 0, sizeof(lineSquare));
    while (j--)
    {
      scanf("%d", &k);
      lineArr[k] = 1;
    }
    init();
    for (i = 1; i; ++i)
    {
      minNum = i;
      if (computed(0))
      {
        printf("%d\n", i);
        break;
      }
    }
  }
  return 0;
}
