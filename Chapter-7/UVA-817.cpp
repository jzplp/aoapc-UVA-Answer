#include <stdio.h>
#include <string.h>

char arr1[20];
int len1;
char arr2[20];
int len2;
int resLen;

void output(int flag)
{
  for (int i = 0; i < (flag == 1 ? len1 : len2); ++i)
  {
    if (flag == 2)
      putchar(arr2[i]);
    if (flag == 1 && arr1[i])
      putchar(arr1[i]);
  }
  printf("=\n");
}

bool isNumber(char c)
{
  if (c >= '0' && c <= '9')
    return true;
  return false;
}

// 结点 计算值使用
struct Node
{
  bool isNumber;
  int value;
};

Node NodeList[20];
int nodeListLen = 0;
Node NodeListT[20];
int nodeListLenT = 0;

// 将数据复制到临时数组中
void copyArr2()
{
  int i, j;
  for (i = 0, j = 0; i < len1; ++i)
  {
    if (arr1[i] != 0)
      arr2[j++] = arr1[i];
  }
  len2 = j;
}

// 判断是否符合前导0条件
bool judgeZero()
{
  int i, j, k;
  // 首位0
  if (arr2[0] == '0')
  {
    if (len2 == 1 || isNumber(arr2[1]))
      return false;
  }
  for (i = 1; i < len2; ++i)
  {
    if (isNumber(arr2[i]))
      continue;
    if (arr2[i + 1] == '0' && i + 2 < len2)
    {
      if (isNumber(arr2[i + 2]))
        return false;
    }
  }
  return true;
}

// 必须有符号
bool hasSign()
{
  int i, n = 0;
  for (i = 0; i < len2; ++i)
  {
    if (arr2[i] == '+' || arr2[i] == '-' || arr2[i] == '*')
      ++n;
  }
  return n ? true : false;
}

// 将分离数字字符串转换成真正的数字，与符号一起放到NodeList中
void setNodeList()
{
  nodeListLen = 0;
  int i = 0, j = 0, k;
  while (i < len2)
  {
    if (!isNumber(arr2[i]))
    {
      NodeList[j++] = {false, arr2[i++]};
      continue;
    }
    k = 0;
    while (i < len2 && isNumber(arr2[i]))
    {
      k = k * 10 + arr2[i] - '0';
      ++i;
    }
    NodeList[j++] = {true, k};
  }
  nodeListLen = j;
}

// 计算结果是否符合2000
bool count()
{
  int i, j, k, value;
  // 首先计算乘法，优先级高 同时复制一份到临时数组
  for (i = 0, j = 0; i < nodeListLen; ++i)
  {
    if (NodeList[i].isNumber)
      NodeListT[j++] = NodeList[i];
    if (!NodeList[i].isNumber)
    {
      if (NodeList[i].value == '*')
      {
        value = NodeListT[j - 1].value * NodeList[i + 1].value;
        NodeListT[j - 1] = {true, value};
        i++;
      }
      else
      {
        NodeListT[j++] = NodeList[i];
      }
    }
  }
  nodeListLenT = j;

  // 计算加减法
  value = NodeListT[0].value;
  i = 1;
  while (i < nodeListLenT)
  {
    if (NodeListT[i].value == '+')
      value += NodeListT[i + 1].value;
    if (NodeListT[i].value == '-')
      value -= NodeListT[i + 1].value;
    i += 2;
  }
  return value == 2000;
}

void judge()
{
  if (len1 <= 1)
    return;
  copyArr2();
  if (!hasSign())
    return;
  if (!judgeZero())
    return;
  setNodeList();
  // 判断等式是否等于2000
  if (!count())
    return;
  // 输出结果
  printf("  ");
  output(2);
  resLen++;
}

void dfs(int n)
{
  if ((n + 1) * 2 > len1)
  {
    judge();
    return;
  }
  arr1[n * 2 + 1] = '*';
  dfs(n + 1);
  arr1[n * 2 + 1] = '+';
  dfs(n + 1);
  arr1[n * 2 + 1] = '-';
  dfs(n + 1);
  arr1[n * 2 + 1] = 0;
  dfs(n + 1);
}

int main()
{
  int t = 0, i, j;
  char c;
  while (1)
  {
    ++t;
    memset(arr1, 0, sizeof(arr1));
    memset(arr2, 0, sizeof(arr2));
    len1 = 0;
    resLen = 0;
    len2 = 0;
    for (i = 0;; i = i + 2)
    {
      c = getchar();
      arr1[i] = c;
      if (c == '=')
        break;
    }
    if (i == 0)
      return 0;
    len1 = i - 1;
    while (getchar() != '\n')
      ;
    printf("Problem %d\n", t);
    dfs(0);
    if (resLen == 0)
    {
      printf("  IMPOSSIBLE\n");
      continue;
    }
  }

  return 0;
}
