#include <stdio.h>

int arr[2][55][55];

char output(int i)
{
  if (i < 26)
  {
    return i + 'A';
  }
  return i - 26 + 'a';
}

int main()
{
  int i, j, k, n;
  while (scanf("%d", &n) > 0)
  {
    for (i = 0; i < n; ++i)
    {
      for (j = 0; j < n; ++j)
      {
        arr[0][i][j] = i;
        arr[1][i][j] = j;
      }
    }
    printf("%d %d %d\n", 2, n, n);
    for (i = 0; i < n; ++i)
    {
      for (j = 0; j < n; ++j)
        printf("%c", output(arr[0][i][j]));
      putchar('\n');
    }
    putchar('\n');
    for (i = 0; i < n; ++i)
    {
      for (j = 0; j < n; ++j)
        printf("%c", output(arr[1][i][j]));
      putchar('\n');
    }
    putchar('\n');
  }
}