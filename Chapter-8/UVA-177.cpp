#include <stdio.h>
#include <string.h>
#define MAXN 8195

// 每种折叠次数对应的折痕序列 0 顺时针 1 逆时针
int foldsArr[14][MAXN];
// foldn 现有的折叠次数长度
int n, foldn;
// 折痕图序列 x y 0为_ 1为|
int figureArr[MAXN][3];
int figureLen;
// 折痕图
char figure[MAXN][MAXN];
int maxx, maxy;

// 计算折痕序列长度
int getFoldsLen(int a)
{
  return (1 << a) - 1;
}

// 生成折痕序列
void genFoldArr(int a)
{
  if (a == 1)
  {
    foldsArr[1][0] = 1;
    return;
  }
  int i;
  int alen = getFoldsLen(a);
  int ailen = getFoldsLen(a - 1);
  for (i = 0; i < ailen; ++i)
  {
    foldsArr[a][i] = foldsArr[a - 1][i];
    foldsArr[a][alen - 1 - i] = foldsArr[a - 1][i] == 1 ? 0 : 1;
  }
  foldsArr[a][ailen] = 1;
}
// 调试输出折痕序列
void outFoldArr()
{
  int i, j, jmax;
  for (i = 1; i < foldn; ++i)
  {
    jmax = (1 << i) - 1;
    printf("%d: ", i);
    for (j = 0; j < jmax; ++j)
      printf("%d ", foldsArr[i][j]);
    printf("\n");
  }
}

// 调试输出折痕图序列
void outFigureArr()
{
  int i;
  // 折痕序列长度
  int len = getFoldsLen(n);
  for (i = 0; i <= len; ++i)
    printf("-- %d %d %d\n", figureArr[i][0], figureArr[i][1], figureArr[i][2]);
  putchar('\n');
}

/*
  StepsX[i][j][k]
  i=0 _  i=1 |
  j为折痕的0和1
  k=0 往左或者往上 k=1 往右或者往下
  StepsX 值为x坐标
  StepsY 值为y坐标
  StepsD 值为下一步方向，就是k
*/
int StepsX[2][2][2] = {{{0, -1}, {-1, 0}}, {{1, 0}, {1, 0}}};
int StepsY[2][2][2] = {{{-1, 1}, {-1, 1}}, {{1, -1}, {-1, 1}}};
int StepsD[2][2][2] = {{{0, 1}, {1, 0}}, {{1, 0}, {0, 1}}};

// 生成折痕图序列
void genFigureArr()
{
  int i;
  // 折痕序列长度
  int len = getFoldsLen(n);
  // 生成折痕图序列
  figureArr[0][0] = 0;
  figureArr[0][1] = 0;
  figureArr[0][2] = 0;
  int d = 1; // 方向
  for (i = 0; i < len; ++i)
  {
    figureArr[i + 1][0] = figureArr[i][0] + StepsX[figureArr[i][2]][foldsArr[n][i]][d];
    figureArr[i + 1][1] = figureArr[i][1] + StepsY[figureArr[i][2]][foldsArr[n][i]][d];
    figureArr[i + 1][2] = figureArr[i][2] == 1 ? 0 : 1;
    d = StepsD[figureArr[i][2]][foldsArr[n][i]][d];
  }
}

// 生成折痕图
void genFigure()
{
  int i, j, k;
  // 折痕图序列长度
  int len = getFoldsLen(n) + 1;
  int minx = figureArr[0][0];
  int miny = figureArr[0][1];
  maxx = 0;
  maxy = 0;
  for (i = 0; i < len; ++i)
  {
    if (minx > figureArr[i][0])
      minx = figureArr[i][0];
    if (miny > figureArr[i][1])
      miny = figureArr[i][1];
  }
  for (i = 0; i < len; ++i)
  {
    figureArr[i][0] -= minx;
    figureArr[i][1] -= miny;
    if (maxx < figureArr[i][0])
      maxx = figureArr[i][0];
    if (maxy < figureArr[i][1])
      maxy = figureArr[i][1];
  }
  memset(figure, 0, sizeof(figure));
  for (i = 0; i < len; ++i)
    figure[figureArr[i][0]][figureArr[i][1]] = figureArr[i][2] == 1 ? '|' : '_';
}

// 输出折痕图
void outFigure()
{
  int i, j;
  // 所有空白转成空格
  for (i = 0; i <= maxx; ++i)
  {
    for (j = 0; j <= maxy; ++j)
      figure[i][j] = figure[i][j] ? figure[i][j] : ' ';
  }
  // 末尾的空格不要否则PE
  for (i = 0; i <= maxx; ++i)
  {
    for (j = maxy; figure[i][j] == ' '; --j)
      figure[i][j] = 0;
  }
  for (i = maxx; i >= 0; --i)
  {
    printf("%s", figure[i]);
    putchar('\n');
  }
  printf("^\n");
}

int main()
{
  int i;
  foldn = 1;
  while (scanf("%d", &n) > 0 && n > 0)
  {
    if (foldn <= n)
    {
      for (i = foldn; i <= n; ++i)
        genFoldArr(i);
      foldn = n + 1;
    }
    genFigureArr();
    genFigure();
    outFigure();
  }
  return 0;
}
