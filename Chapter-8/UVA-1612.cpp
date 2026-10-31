#include <stdio.h>
#include <math.h>
#define MAXN 16400

double scoreArr[MAXN][3];
int rankArr[MAXN];
int n;
double v;
double darr[10];

int compare(double a, double b)
{
  if (abs(a - b) < 1e-6) return 0;
  if(a > b) return 1;
  return -1;
}

bool judge(int i, double v1, int j, double v2)
{
  if (compare(v1, v2) > 0)
    return true;
  if (compare(v1, v2) == 0 && i < j)
    return true;
  return false;
}

void sort(double *arr, int len)
{
  int a, b, c;
  double d;
  for (a = 1; a <= len; ++a)
  {
    c = a;
    for (b = a + 1; b <= len; ++b)
    {
      if (compare(arr[c], arr[b]) < 0)
        c = b;
    }
    if (c != a)
    {
      d = arr[a];
      arr[a] = arr[c];
      arr[c] = d;
    }
  }
}

void print(double *arr, int len)
{
  for (int i = 1; i <= len; ++i)
    printf("%.2lf ", arr[i]);
  putchar('\n');
}

bool computed()
{
  v = scoreArr[rankArr[1]][0] + scoreArr[rankArr[1]][1] + scoreArr[rankArr[1]][2];
  int vi = rankArr[1];
  double v1, v2;
  int i, j, k;
  for (i = 2; i <= n; ++i)
  {
    double darr[10] = {
        0,
        scoreArr[rankArr[i]][0] + scoreArr[rankArr[i]][1] + scoreArr[rankArr[i]][2],
        scoreArr[rankArr[i]][0] + scoreArr[rankArr[i]][1],
        scoreArr[rankArr[i]][0] + scoreArr[rankArr[i]][2],
        scoreArr[rankArr[i]][1] + scoreArr[rankArr[i]][2],
        scoreArr[rankArr[i]][0],
        scoreArr[rankArr[i]][1],
        scoreArr[rankArr[i]][2],
        0};
    sort(darr, 8);
    // print(darr, 8);
    for (j = 1; j <= 8; ++j)
    {
      v1 = darr[j];
      if (judge(vi, v, rankArr[i], v1))
      {
        v = v1;
        vi = rankArr[i];
        break;
      }
    }
    if (j == 9)
      return false;
  }
  return true;
}

int main()
{
  int i, j, k = 0;
  int i1, i2, i3;
  while (scanf("%d", &n) > 0 && n > 0)
  {
    ++k;
    for (i = 1; i <= n; ++i)
      scanf("%lf %lf %lf\n", &scoreArr[i][0], &scoreArr[i][1], &scoreArr[i][2]);
    for (i = 1; i <= n; ++i)
      scanf("%d", &rankArr[i]);
    printf("Case %d: ", k);
    if (!computed())
      printf("No solution\n");
    else
      printf("%.2lf\n", v);
  }
  return 0;
}