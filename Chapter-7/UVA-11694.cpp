#include <stdio.h>
#include <string.h>

// 1 / -1 \ 0 空
int arrLine[10][10];
int arrLineLoop[10][10];
int arrSec[10][10];
int n;

// 入参为交叉点坐标
int getSecNum(int x, int y)
{
    int num = 0;
    // 左上角
    if (x != 0 && y != 0)
        num += arrLine[x - 1][y - 1] == -1;
    // 右上角
    if (x != 0 && y != n)
        num += arrLine[x - 1][y] == 1;
    // 左下角
    if (x != n && y != 0)
        num += arrLine[x][y - 1] == 1;
    // 右下角
    if (x != n && y != n)
        num += arrLine[x][y] == -1;
    return num;
}

// 入参为方块坐标
bool judgeSec(int x, int y)
{
    int num;
    // 左上角
    if (arrSec[x][y] != -1 && getSecNum(x, y) != arrSec[x][y])
        return false;
    // 右上角
    num = getSecNum(x, y + 1);
    if (arrSec[x][y + 1] != -1)
    {
        if (y == n - 1 && num != arrSec[x][y + 1])
            return false;
        if (num > arrSec[x][y + 1])
            return false;
    }
    // 左下角
    num = getSecNum(x + 1, y);
    if (arrSec[x + 1][y] != -1)
    {
        if (x == n - 1 && num != arrSec[x + 1][y])
            return false;
        if (num > arrSec[x + 1][y])
            return false;
    }
    // 右下角
    num = getSecNum(x + 1, y + 1);
    if (arrSec[x + 1][y + 1] != -1)
    {
        if (x == n - 1 && y == n - 1 && num != arrSec[x + 1][y + 1])
            return false;
        if (num > arrSec[x + 1][y + 1])
            return false;
    }
    return true;
}

// 交叉点坐标终点
int endx, endy;

// 入参为交叉点坐标
bool loop(int x, int y, bool init)
{
    if (!init && x == endx && y == endy)
        return true;
    // 向左上
    if (x != 0 && y != 0 && !arrLineLoop[x - 1][y - 1] && arrLine[x - 1][y - 1] == -1)
    {
        arrLineLoop[x - 1][y - 1] = 1;
        if (loop(x - 1, y - 1, false))
            return true;
        arrLineLoop[x - 1][y - 1] = 0;
    }
    // 向右上
    if (x != 0 && y != n && !arrLineLoop[x - 1][y] && arrLine[x - 1][y] == 1)
    {
        arrLineLoop[x - 1][y] = 1;
        if (loop(x - 1, y + 1, false))
            return true;
        arrLineLoop[x - 1][y] = 0;
    }
    // 向左下
    if (x != n && y != 0 && !arrLineLoop[x][y - 1] && arrLine[x][y - 1] == 1)
    {
        arrLineLoop[x][y - 1] = 1;
        if (loop(x + 1, y - 1, false))
            return true;
        arrLineLoop[x][y - 1] = 0;
    }
    // 向右下
    if (x != n && y != n && !arrLineLoop[x][y] && arrLine[x][y] == -1)
    {
        arrLineLoop[x][y] = 1;
        if (loop(x + 1, y + 1, false))
            return true;
        arrLineLoop[x][y] = 0;
    }
    return false;
}

// 入参为交叉点坐标
bool judgeLoop(int x, int y)
{
    endx = x;
    endy = y;
    memset(arrLineLoop, 0, sizeof(arrLineLoop));
    if (loop(x, y, true))
        return false;
    return true;
}

// 入参为方块坐标
bool computed(int x, int y)
{
    if (x >= n)
        return true;
    if (y >= n)
        return computed(x + 1, 0);
    arrLine[x][y] = 1;
    if (judgeSec(x, y) && judgeLoop(x, y + 1) && computed(x, y + 1))
        return true;
    arrLine[x][y] = -1;
    if (judgeSec(x, y) && judgeLoop(x, y) && computed(x, y + 1))
        return true;
    arrLine[x][y] = 0;
    return false;
}

int main()
{
    int N, i, j;
    char c;
    scanf("%d", &N);
    while (N--)
    {
        memset(arrLine, 0, sizeof(arrLine));
        memset(arrSec, 0, sizeof(arrSec));
        scanf("%d", &n);
        for (i = 0; i <= n; ++i)
        {
            getchar();
            for (j = 0; j <= n; ++j)
            {
                c = getchar();
                if (c == '.')
                    arrSec[i][j] = -1;
                else
                    arrSec[i][j] = c - '0';
            }
        }
        computed(0, 0);
        for (i = 0; i < n; ++i)
        {
            for (j = 0; j < n; ++j)
            {
                printf("%c", arrLine[i][j] == 1 ? '/' : '\\');
            }
            putchar('\n');
        }
    }
    return 0;
}
