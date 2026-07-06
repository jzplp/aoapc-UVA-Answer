#include <stdio.h>
#include <set>

using namespace std;

int arr[1000005];
int n;
set<int> se;

int main()
{
  int t, i;
  int l, r;
  int len, mexLen;
  scanf("%d", &t);
  while (t--)
  {
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
      scanf("%d", &arr[i]);
    l = 0;
    r = 0;
    se.clear();
    mexLen = 0;
    while (r < n)
    {
      while (r < n && !se.count(arr[r]))
      {
        se.insert(arr[r]);
        ++r;
      }
      len = r - l;
      if (mexLen < len)
        mexLen = len;
      se.erase(arr[l]);
      ++l;
    }
    printf("%d\n", mexLen);
  }

  return 0;
}