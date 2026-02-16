#include <stdio.h>
#include <vector>
using namespace std;

vector<char> vec[3];
int len;

int str2int(int i)
{
  int num = 0;
  for (int j = 0; j < vec[i].size(); ++j)
  {
    num = num * 10 + (vec[i][j] - '0');
  }
  return num;
}

// 判断等号后面的数字是否符合要求
bool judgeEqual(int res)
{
  int num;
  for (int j = vec[2].size() - 1; j >= 0; --j)
  {
    num = res % 10;
    res = res / 10;
    if (j == 0 && num == 0)
      return false;
    if (vec[2][j] == '*')
      continue;
    if (vec[2][j] - '0' != num)
      return false;
  }
  if (res)
    return false;
  return true;
}

// 输出获取到的数组
void printVec()
{
  for (int i = 0; i < 3; ++i)
  {
    for (auto ip = vec[i].begin(); ip != vec[i].end(); ++ip)
    {
      printf("%c", *ip);
    }
    if (i != 2)
      putchar(' ');
  }
  putchar('\n');
}

// 判断当前数组有几个解 初始调用时传0 0
int judge(int i, int j)
{
  // printf("%d %d\n", i, j);
  if (i > 1)
  {
    int a = str2int(0), b = str2int(1);
    // printf("--- %d %d\n", a, b);
    return judgeEqual(a * b) ? 1 : 0;
  }
  if (j >= vec[i].size())
  {
    return judge(i + 1, 0);
  }
  if (vec[i][j] == '*')
  {
    int res = 0;
    for (int k = 0; k < 10; ++k)
    {
      if (k == 0 && j == 0)
        continue;
      vec[i][j] = '0' + k;
      res += judge(i, j + 1);
    }
    vec[i][j] = '*';
    return res;
  }
  return judge(i, j + 1);
}

// i，j 目前到第几个数字 num 还有几个数字需要变换
int tryLoop(int i, int j, int num, int remain)
{
  if (i > 2 || num == 0)
  {
    int res = judge(0, 0);
    if (res == 1)
      return true;
    return false;
  }
  if (j == vec[i].size())
  {
    return tryLoop(i + 1, 0, num, remain);
  }

  int tempValue = vec[i][j];
  char c;

  // 变化但是字典序低
  for (int k = -1; k <= 9; ++k)
  {
    if (k == -1)
      c = '*';
    else
      c = k + '0';
    if (tempValue <= c)
      continue;
    if (j == 0 && c == '0')
      continue;
    vec[i][j] = c;
    if (tryLoop(i, j + 1, num - 1, remain - 1))
      return true;
  }

  // 不变化
  if (num < remain)
  {
    vec[i][j] = tempValue;
    if (tryLoop(i, j + 1, num, remain - 1))
      return true;
  }

  // 变化但是字典序高
  for (int k = -1; k <= 9; ++k)
  {
    if (k == -1)
      c = '*';
    else
      c = k + '0';
    if (tempValue >= c)
      continue;
    if (j == 0 && c == '0')
      continue;
    vec[i][j] = c;
    if (tryLoop(i, j + 1, num - 1, remain - 1))
      return true;
  }

  vec[i][j] = tempValue;
  return false;
}

// 以改变数字个数循环
void loop()
{
  int i, j, k;
  for (int i = 1; i <= len; ++i)
  {
    // printf("--- %d\n", i);
    // 改变i个数字
    if (tryLoop(0, 0, i, len))
      return;
  }
}

int main()
{
  int n = 0, i, j, k;
  char c;
  while (1)
  {
    i = 0;
    for (j = 0; j < 3; ++j)
      vec[j].clear();
    while (scanf("%c", &c) != EOF)
    {
      // 第一个元素为0
      if (c == '0' && vec[i].size() == 0)
        return 0;
      // 一个数字输入完
      if (c == ' ' || c == '\n')
      {
        ++i;
        if (i == 3)
          break;
        continue;
      }
      vec[i].push_back(c);
    }
    len = vec[0].size() + vec[1].size() + vec[2].size();
    printf("Case %d: ", ++n);
    if (judge(0, 0) != 1)
      loop();
    printVec();
  }
  return 0;
}
