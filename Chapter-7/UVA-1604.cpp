#include <stdio.h>

// 目标状态
int goal[3][3];
// 当前空白位置
int emptyPos[2];
// 当前状态
// stateArr[i][j]为一个立方体的状态 最后一个下标的值表示顶面/上面/右侧面三个颜色值
int stateArr[3][3][3];

int minStep = 31;

// 四个方向移动
int steps[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
// 四个方向的反向 改回去使用
int stepsRe[4] = {1, 0, 3, 2};
// 四个方向的原值如何覆盖为新值的对应关系
int stepChange[4][3] = {
    {1, 0, 2},
    {1, 0, 2},
    {2, 1, 0},
    {2, 1, 0}};

// 判断当前状态是否符合终点状态 0表示符合
int judge()
{
  int n = 0;
  int i, j;
  for (i = 0; i < 3; ++i)
  {
    for (j = 0; j < 3; ++j)
    {
      if (goal[i][j] != stateArr[i][j][0])
        return ++n;
    }
  }
  return n;
}

void dfs(int step, int preStep)
{
  if (step >= minStep)
    return;
  int jnum = judge();
  if (jnum == 0)
  {
    minStep = step;
    return;
  }
  // step + 1 + jnum - 1
  if (step + jnum > 30)
    return;

  int preA = emptyPos[0], preB = emptyPos[1];
  int i, j, k, a, b;
  // 四个方向遍历
  for (i = 0; i < 4; ++i)
  {
    if (stepsRe[i] == preStep)
      continue;
    // 正向旋转过去
    // a,b 要转的位置
    a = steps[i][0] + preA;
    b = steps[i][1] + preB;
    if (a < 0 || a > 2 || b < 0 || b > 2)
      continue;
    for (j = 0; j < 3; ++j)
      stateArr[preA][preB][j] = stateArr[a][b][stepChange[i][j]];
    emptyPos[0] = a;
    emptyPos[1] = b;
    stateArr[a][b][0] = 0;

    dfs(step + 1, i);

    // 反向旋转回来
    for (j = 0; j < 3; ++j)
      stateArr[a][b][j] = stateArr[preA][preB][stepChange[stepsRe[i]][j]];
    emptyPos[0] = preA;
    emptyPos[1] = preB;
    stateArr[preA][preB][0] = 0;
  }
}

int main()
{
  int i, j, k, jnum;
  char c;
  while (scanf("%d %d", &emptyPos[1], &emptyPos[0]) == 2)
  {
    minStep = 1000;
    if (emptyPos[0] == 0 || emptyPos[1] == 0)
      return 0;
    emptyPos[0]--;
    emptyPos[1]--;
    // 读入换行符
    getchar();
    for (i = 0; i < 3; ++i)
    {
      for (j = 0; j < 3; ++j)
      {
        scanf("%c", &c);
        // 白色1 蓝色2 红色3 空0
        switch (c)
        {
        case 'W':
          k = 1;
          break;
        case 'B':
          k = 2;
          break;
        case 'R':
          k = 3;
          break;
        case 'E':
          k = 0;
          break;
        }
        goal[i][j] = k;
        // 读入一个分隔符
        getchar();
      }
    }
    // 初始化当前状态
    for (i = 0; i < 3; ++i)
    {
      for (j = 0; j < 3; ++j)
      {
        stateArr[i][j][0] = 1;
        stateArr[i][j][1] = 3;
        stateArr[i][j][2] = 2;
      }
    }
    stateArr[emptyPos[0]][emptyPos[1]][0] = 0;
    dfs(0, -1);

    if (minStep > 30)
      printf("-1\n");
    else
      printf("%d\n", minStep);
  }
  return 0;
}
