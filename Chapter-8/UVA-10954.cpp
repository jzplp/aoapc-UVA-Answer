#include <stdio.h>
#include <queue>
#include <vector>
#define MAXN 5002
using namespace std;

int n;
int arr[MAXN];

bool cmp(int left, int right)
{
  return left > right;
}

int main()
{
  int i, j, a1, a2, sum;
  while (scanf("%d", &n) > 0 && n != 0)
  {
    priority_queue<int, vector<int>, bool (*)(int, int)> qu(cmp);
    for (i = 0; i < n; ++i)
    {
      scanf("%d", &j);
      qu.push(j);
    }
    sum = 0;
    while (qu.size() != 1)
    {
      a1 = qu.top();
      qu.pop();
      a2 = qu.top();
      qu.pop();
      a1 += a2;
      sum += a1;
      qu.push(a1);
    }
    printf("%d\n", sum);
  }
  return 0;
}