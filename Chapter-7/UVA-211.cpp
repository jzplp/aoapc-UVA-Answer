#include <stdio.h>
#include <string.h>

// dominoes牌列表 序号 1-28
int domino[29][2] = {
    {},
    {0, 0},
    {0, 1},
    {0, 2},
    {0, 3},
    {0, 4},
    {0, 5},
    {0, 6},
    {1, 1},
    {1, 2},
    {1, 3},
    {1, 4},
    {1, 5},
    {1, 6},
    {2, 2},
    {2, 3},
    {2, 4},
    {2, 5},
    {2, 6},
    {3, 3},
    {3, 4},
    {3, 5},
    {3, 6},
    {4, 4},
    {4, 5},
    {4, 6},
    {5, 5},
    {5, 6},
    {6, 6},
};

// 方向 由于是从上到下，从左到右搜索，因此上和左肯定不会再走
int steps[2][2] = {{1, 0}, {0, 1}};

int set[7][8];
int map[7][8];
// dominoes牌 是否使用过
int useDomino[29];
// map数量
int number;

void showMap()
{
  int i, j;
  for (i = 0; i < 7; ++i)
  {
    for (j = 0; j < 8; ++j)
      printf("%4d", map[i][j]);
    putchar('\n');
  }
  printf("\n\n");
}

void init()
{
  memset(map, 0, sizeof(map));
  memset(useDomino, 0, sizeof(useDomino));
  number = 0;
}

void computed(int n)
{
  // showMap();
  if (n == 56)
  {
    ++number;
    showMap();
    return;
  }
  int x = n / 8;
  int y = n % 8;
  if (map[x][y])
  {
    computed(n + 1);
    return;
  }
  int i, j, k;
  int x1, y1;
  for (i = 0; i < 2; ++i)
  {
    x1 = x + steps[i][0];
    y1 = y + steps[i][1];
    if (x1 >= 7 || y1 >= 8 || map[x1][y1])
      continue;
    for (j = 1; j <= 28; ++j)
    {
      if (useDomino[j])
        continue;
      if ((set[x][y] == domino[j][0] && set[x1][y1] == domino[j][1]) || (set[x][y] == domino[j][1] && set[x1][y1] == domino[j][0]))
      {
        useDomino[j] = 1;
        map[x][y] = j;
        map[x1][y1] = j;
        computed(n + 1);
        useDomino[j] = 0;
        map[x][y] = 0;
        map[x1][y1] = 0;
      }
    }
  }
}

int main()
{
  int i, j;
  int count = 0;

  while (1)
  {
    ++count;
    for (i = 0; i < 7; ++i)
    {
      for (j = 0; j < 8; ++j)
      {
        if (scanf("%d", &set[i][j]) != 1)
        {
          return 0;
        }
      }
    }
    if (count != 1)
      printf("\n\n\n\n\n");
    printf("Layout #%d:\n\n\n", count);
    for (i = 0; i < 7; ++i)
    {
      for (j = 0; j < 8; ++j)
        printf("%4d", set[i][j]);
      putchar('\n');
    }
    putchar('\n');
    printf("Maps resulting from layout #%d are:\n\n\n", count);
    init();
    computed(0);
    printf("There are %d solution(s) for layout #%d.\n", number, count);
  }
  return 0;
}