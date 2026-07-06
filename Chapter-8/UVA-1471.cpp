#include <stdio.h>
#include <string.h>
#include <set>

using namespace std;

#define MAXN 200005

int arr[MAXN];
int n;
// leftArr是以i开头的连续子序列长度
// rightArr是以i结尾的连续子序列长度
int leftArr[MAXN], rightArr[MAXN];

struct Stu
{
  int arrV;
  int value;
};

bool operator<(const Stu &left, const Stu right)
{
  if (left.arrV != right.arrV)
    return left.arrV < right.arrV;
  return left.value < right.value;
}

set<Stu> se;

void init()
{
  se.clear();
  int i, left;
  memset(leftArr, 0, sizeof(leftArr));
  memset(rightArr, 0, sizeof(rightArr));
  leftArr[0] = 1;
  left = 0;
  for (i = 1; i < n; ++i)
  {
    if (arr[i] > arr[i - 1])
    {
      ++leftArr[left];
      if (i == n - 1)
        rightArr[i] = leftArr[left];
    }
    else
    {
      rightArr[i - 1] = leftArr[left];
      left = i;
      leftArr[i] = 1;
      if (i == n - 1)
        rightArr[i] = 1;
    }
  }
  for (i = 1; i < n; ++i)
  {
    if (leftArr[i])
      continue;
    leftArr[i] = leftArr[i - 1] - 1;
  }
  for (i = n - 1; i >= 0; --i)
  {
    if (rightArr[i])
      continue;
    rightArr[i] = rightArr[i + 1] - 1;
  }

  // output
  /*
  for (i = 0; i < n; ++i)
    printf("%2d ", arr[i]);
  putchar('\n');
  for (i = 0; i < n; ++i)
    printf("%2d ", leftArr[i]);
  putchar('\n');
  for (i = 0; i < n; ++i)
    printf("%2d ", rightArr[i]);
  putchar('\n');
  */
}

int computed()
{
  int i, j, k;
  bool flag;
  int value, maxValue = leftArr[0];
  for (i = 1; i < n; ++i)
  {
    Stu item = {arr[i - 1], rightArr[i - 1]};
    se.insert(item);
    auto ip = se.find(item);
    flag = false;
    if (ip != se.begin())
    {
      ip--;
      // 如果前一个元素的值大于当前元素，那么当前值没有插入的必要
      if (ip->value >= item.value)
      {
        se.erase(item);
        flag = true;
      }
      else if (ip->arrV == item.arrV) // arr[i]的值相等，且当前值value更大，则前一个值没有存在的必要
        se.erase(ip);
    }
    if (!flag)
    {
      // 向后删除value值更小，没有存在必要的元素
      ip = se.find(item);
      ++ip;
      while (ip != se.end())
      {
        if (ip->value <= item.value)
          se.erase(ip++);
        else
          break;
      }
    }
    // 对于rightArr[i], 从set中找最合适的元素
    ip = se.lower_bound({arr[i], 0});
    if (ip == se.begin())
      value = ip->value;
    else
    {
      --ip;
      value = leftArr[i] + ip->value;
    }
    if (value > maxValue)
      maxValue = value;
  }
  return maxValue;
}

int main()
{
  int t, i;
  scanf("%d", &t);
  while (t--)
  {
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
      scanf("%d", &arr[i]);
    init();
    printf("%d\n", computed());
  }
  return 0;
}