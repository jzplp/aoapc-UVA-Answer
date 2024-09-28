#include <stdio.h>
#include <string.h>
#define MAXN 21
#define STEP_NUM 5
#define TASK_NUM 10

int n;
int program[MAXN][STEP_NUM];
int minLen, minInterval;
int steps[TASK_NUM];

void init()
{
  memset(program, 0, sizeof(program));
  memset(steps, 0, sizeof(steps));
  minLen = TASK_NUM * n;
  minInterval = -1;
}

// 判断当前有没有冲突
bool test(int s, int a)
{
  int i, j, k;
  int pos;
  // 对第s+1个执行循环步骤
  for (i = 0; i < n; ++i)
  {
    // 当前位置
    pos = steps[s] + a + i;
    // 对前面已经执行过的步骤判断是否与当前执行冲突
    for (j = s; j >= 0; --j)
    {
      if (steps[j] + n <= pos)
      {
        if (j == s)
          return true;
        break;
      }
      for (k = 0; k < STEP_NUM; ++k)
      {
        if (program[i][k] != 0 && program[pos - steps[j]][k] == program[i][k])
          return false;
      }
    }
  }
  return true;
}

void compute(int s)
{
  if (s == TASK_NUM - 1)
  {
    if (steps[s] + n < minLen)
      minLen = steps[s] + n;
    return;
  }
  int i, j;
  for (i = 0; i <= n; ++i)
  {
    if (steps[s] + i + n + ((TASK_NUM - s - 2) * (minInterval == -1 ? 0 : minInterval)) >= minLen)
      return;
    if (!test(s, i))
      continue;
    if (s == 0 && minInterval == -1)
      minInterval = i;
    steps[s + 1] = steps[s] + i;
    compute(s + 1);
  }
}

int main()
{
  int i, j, k;
  char c;
  while (scanf("%d", &n) == 1 && n > 0)
  {
    init();
    for (i = 0; i < STEP_NUM; ++i)
    {
      getchar();
      for (j = 0; j < n; ++j)
      {
        c = getchar();
        if (c == 'X')
          program[j][i] = 1;
      }
    }
    steps[0] = 0;
    compute(0);
    printf("%d\n", minLen);
  }
  return 0;
}