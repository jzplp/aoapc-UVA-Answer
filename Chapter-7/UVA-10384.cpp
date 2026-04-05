#include <stdio.h>
#include <string.h>

int arrWall[8][8];
int Steps[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
char StepConvert[4] = {'W', 'N', 'E', 'S'};
char StepRe[4] = {2, 3, 0, 1};
int stepArr[100000];

int stepMax;

bool outXY(int x, int y)
{
    if (x < 0 || x >= 4 || y < 0 || y >= 6)
        return true;
    return false;
}

void setWall(int x, int y, int i, bool set)
{
    int newX = x + Steps[i][0];
    int newY = y + Steps[i][1];
    int newnewX = newX + Steps[i][0];
    int newnewY = newY + Steps[i][1];
    int k = 1 << i;
    int rei = StepRe[i];
    int rek = 1 << rei;
    if (set)
    {
        arrWall[newX][newY] -= rek;
        arrWall[newX][newY] += k;
        arrWall[x][y] -= k;
        if (!outXY(newnewX, newnewY))
            arrWall[newnewX][newnewY] += rek;
        return;
    }
    arrWall[newX][newY] += rek;
    arrWall[newX][newY] -= k;
    arrWall[x][y] += k;
    if (!outXY(newnewX, newnewY))
        arrWall[newnewX][newnewY] -= rek;
}

bool computed(int x, int y, int stepNum)
{
    if (outXY(x, y))
        return true;
    if (stepNum >= stepMax)
        return false;
    int i, j, k, newX, newY;
    bool hasWall;
    for (i = 0; i < 4; ++i)
    {
        k = 1 << i;
        newX = x + Steps[i][0];
        newY = y + Steps[i][1];
        hasWall = false;
        // 有墙
        if (arrWall[x][y] & k)
        {
            hasWall = true;
            // 到边缘
            if (outXY(newX, newY))
                continue;
            // 再隔一层也有墙
            if (arrWall[newX][newY] & k)
                continue;
            setWall(x, y, i, true);
        }
        stepArr[stepNum] = i;
        if (computed(newX, newY, stepNum + 1))
            return true;
        // 回退墙
        if (hasWall)
            setWall(x, y, i, false);
    }
    return false;
}

int main()
{
    int x, y, t;
    int i, j, k;
    while (scanf("%d %d", &x, &y) == 2 && x != 0 && y != 0)
    {
        t = x;
        x = y;
        y = t;
        x = x - 1;
        y = y - 1;
        memset(arrWall, 0, sizeof(arrWall));
        for (i = 0; i < 4; ++i)
        {
            for (j = 0; j < 6; ++j)
                scanf("%d", &arrWall[i][j]);
        }
        for (i = 0;; ++i)
        {
            stepMax = i;
            if (computed(x, y, 0))
                break;
        }
        for (j = 0; j < i; ++j)
            putchar(StepConvert[stepArr[j]]);
        putchar('\n');
    }
    return 0;
}