#include <stdio.h>
#include <string.h>

// 1 横线 2 竖线
int map[5][9];
int mapt[7][5][9];
int spuare[8][3] = {{0, 1, 1}, {0, 3, 1}, {1, 0, 2}, {1, 4, 2}, {2, 0, 2}, {2, 4, 2}, {2, 1, 1}, {2, 3, 1}};

void init()
{
  memset(map, 0, sizeof(map));
  memset(mapt, 0, sizeof(mapt));
}

bool input()
{
  int i, j;
  char c;
  for (i = 0; i < 5; ++i)
  {
    for (j = 0; j < 10; ++j)
    {
      scanf("%c", &c);
      if (c == '0')
        return false;
      if (c == ' ')
        map[i][j] = 0;
      if (c == '_')
        map[i][j] = 1;
      if (c == '|')
        map[i][j] = 2;
      if (c == '#')
        scanf("%c", &c);
    }
  }
  for (i = 0; i < 5; ++i)
    for (j = 0; j < 9; ++j)
      mapt[0][i][j] = map[i][j];
  return true;
}

void printMap(int t)
{
  int i, j;
  for (i = 0; i < 5; ++i)
  {
    for (j = 0; j < 9; ++j)
      printf("%d", mapt[t][i][j]);
    putchar('\n');
  }
  putchar('\n');
}

void copyMap(int k)
{
  int i, j;
  for (i = 0; i < 5; ++i)
    for (j = 0; j < 9; ++j)
      mapt[k][i][j] = mapt[k - 1][i][j];
}

bool subSquare(int t, int i, int j, int k)
{
  int a, b, inew, jnew;
  int isub = i - spuare[k][0];
  int jsub = j - spuare[k][1];
  // 首先8条边符合
  for (a = 0; a < 8; ++a)
  {
    inew = isub + spuare[a][0];
    jnew = jsub + spuare[a][1];
    if (inew < 0 || inew >= 5 || jnew < 0 || jnew >= 9)
      return false;
      // t == 1时，8条边必须都存在
    if(t == 1 && !mapt[t][inew][jnew]) return false;
    mapt[t][inew][jnew] = 0;
  }
  // 8条边中间不能有内容
  for(i = 1; i < 3; ++i) {
    for(j = 1; j < 4; ++j) {
      inew = isub + i;
      jnew = jsub + j;
      if(mapt[t][inew][jnew]) return false;
    }
  }
  return true;
}

bool clear(int t)
{
  int i, j;
  for (i = 0; i < 5; ++i)
    for (j = 0; j < 9; ++j)
    {
      if (mapt[t][i][j])
        return false;
    }
  return true;
}

bool computed(int t)
{
  // printMap(t);
  if (clear(t))
    return true;
  if (t >= 6)
    return false;
  int i, j, k;
  for (i = 0; i < 5; ++i)
  {
    for (j = 0; j < 9; ++j)
    {
      if (!mapt[t][i][j])
        continue;
      for (k = 0; k < 8; ++k)
      {
        if (spuare[k][2] != mapt[t][i][j])
          continue;
        copyMap(t + 1);
        // printf("%d %d %d %d %d\n", t, i, j, k, subSquare(t + 1, i, j, k));
        if (!subSquare(t + 1, i, j, k))
          continue;
        if (computed(t + 1))
          return true;
      }
    }
  }
  return false;
}

int main()
{
  int i = 0;
  while (1)
  {
    ++i;
    init();
    if (!input())
      break;
    printf("Case %d: ", i);
    if (computed(0))
      printf("Yes\n");
    else
      printf("No\n");
  }
  return 0;
}