#include <stdio.h>
#include <string.h>
#include <queue>

using namespace std;

// 数组
int arr[5][5];
// 数组
int arrNew[5][5];
// 编号对应数组的下标 i*10+j 编号从0开始
int arrIndex[15] = {0, 10, 1, 20, 11, 2, 30, 21, 12, 3, 40, 31, 22, 13, 4};
// 数组下标对应编号
int arrReIndex[100];
// 六个方向
int steps[6][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 0}, {1, -1}, {0, -1}};
int endi, endj;

int indexResL[10000][2];
int indexResR[10000][2];
int len;

struct Path
{
  // 是否查找到
  bool isFind;
  // 上一步的路径
  int preStatus;
  // 起始点
  int i1, j1;
  // 终点
  int i2, j2;
  // 步数
  int num;
};

// 状态是否访问过
Path map[40000];

struct Node
{
  // 状态
  int status;
  // 步数
  int num;
};

queue<Node> qu;

void setRes(Path p, bool flag = false)
{
  for (int i = p.num - 1; i >= 0; --i)
  {
    if (!flag)
    {
      indexResL[i][0] = arrReIndex[p.i1 * 10 + p.j1];
      indexResL[i][1] = arrReIndex[p.i2 * 10 + p.j2];
    }
    else
    {
      indexResR[i][0] = arrReIndex[p.i1 * 10 + p.j1];
      indexResR[i][1] = arrReIndex[p.i2 * 10 + p.j2];
    }
    p = map[p.preStatus];
  }
}

bool compare(int num)
{
  for (int i = 0; i < num; ++i)
  {
    if (indexResL[i][0] > indexResR[i][0])
      return true;
    if (indexResL[i][0] < indexResR[i][0])
      return false;
    if (indexResL[i][1] > indexResR[i][1])
      return true;
    if (indexResL[i][1] < indexResR[i][1])
      return false;
  }
  return false;
}

bool judge()
{
  int i, j, k;
  for (i = 0; i < 5; ++i)
  {
    for (j = 0; j < (5 - i); ++j)
      if (i == endi && j == endj)
      {
        if (arr[i][j] == 0)
          return false;
      }
      else
      {
        if (arr[i][j] != 0)
          return false;
      }
  }
  return true;
}

int arr2Int(bool isNew)
{
  int i, j, num = 0;
  for (i = 0; i < 5; ++i)
  {
    for (j = 0; j < (5 - i); ++j)
      num = num * 2 + (isNew ? arrNew[i][j] : arr[i][j]);
  }
  return num;
}

void int2Arr(int num)
{
  int i, j, k;
  for (i = 4; i >= 0; --i)
  {
    for (j = (5 - i) - 1; j >= 0; --j)
    {
      arr[i][j] = num % 2;
      num /= 2;
    }
  }
}

void resetArrNew()
{
  int i, j;
  for (i = 0; i < 5; ++i)
    for (j = 0; j < (5 - i); ++j)
      arrNew[i][j] = arr[i][j];
}

void bfs()
{
  int i1, i2, i3, i4, flag;
  int a, b;
  Node no;
  qu.push({arr2Int(false), 0});
  while (!qu.empty())
  {
    no = qu.front();
    qu.pop();
    int2Arr(no.status);
    if (len && len < no.num)
      return;
    if (judge())
    {
      len = no.num;
      setRes(map[no.status]);
      return;
    }
    for (i1 = 0; i1 < 5; ++i1)
    {
      for (i2 = 0; i2 < (5 - i1); ++i2)
      {
        if (!arr[i1][i2])
          continue;
        for (i3 = 0; i3 < 6; ++i3)
        {
          resetArrNew();
          a = i1;
          b = i2;
          flag = 0;
          for (i4 = 0;; ++i4)
          {
            a = a + steps[i3][0];
            b = b + steps[i3][1];
            if (a < 0 || b < 0 || a >= 5 || b >= (5 - a))
              break;
            if (arrNew[a][b] == 0)
            {
              flag = 1;
              break;
            }
            if (arrNew[a][b] == 1)
              arrNew[a][b] = 0;
          }
          if (flag && i4 > 0)
          {
            arrNew[a][b] = 1;
            arrNew[i1][i2] = 0;
            int status = arr2Int(true);
            Path p = {true, no.status, i1, i2, a, b, no.num + 1};
            if (!map[status].isFind)
            {
              qu.push({status, no.num + 1});
              map[status] = p;
              continue;
            }
            // 设置map的逻辑 按照序号字典序表示优先级
            if (map[status].num < (no.num + 1))
              continue;

            setRes(map[status]);
            setRes(p, true);
            if (compare(no.num + 1))
            {
              map[status] = p;
            }
          }
        }
      }
    }
  }
}

int main()
{
  int T = 0, i, j, k;
  memset(arrReIndex, 0, sizeof(arrReIndex));
  for (i = 0; i < 15; ++i)
    arrReIndex[arrIndex[i]] = i;
  scanf("%d", &T);
  while (T--)
  {
    for (i = 0; i < 5; ++i)
    {
      for (j = 0; j < 5; ++j)
        arr[i][j] = 1;
    }
    memset(map, 0, sizeof(map));
    len = 0;
    queue<Node>().swap(qu);
    scanf("%d", &k);
    k -= 1;
    endi = arrIndex[k] / 10;
    endj = arrIndex[k] % 10;
    arr[endi][endj] = 0;

    bfs();
    if (!len)
    {
      printf("IMPOSSIBLE");
      continue;
    }
    printf("%d\n", len);
    for (i = 0; i < len; ++i)
    {
      if (i != 0)
        putchar(' ');
      printf("%d %d", indexResL[i][0] + 1, indexResL[i][1] + 1);
    }
    putchar('\n');
  }
}