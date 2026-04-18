#include <stdio.h>

int arrOrigin[35];
int len;
int arr[35];
int stepArr[70];
int stepLen;

int findMax(int i)
{
    int maxi = i;
    for (int j = i - 1; j >= 0; --j)
    {
        if (arr[j] > arr[maxi])
            maxi = j;
    }
    return maxi;
}

void flip(int i)
{
    int t;
    for (int j = 0; j <= i / 2; ++j)
    {
        t = arr[j];
        arr[j] = arr[i - j];
        arr[i - j] = t;
    }
}

void loop()
{
    int i, maxi;
    for (i = len - 1; i > 0; --i)
    {
        maxi = findMax(i);
        if (maxi == i)
            continue;
        if (maxi != 0)
        {
            flip(maxi);
            stepArr[stepLen++] = maxi;
        }
        flip(i);
        stepArr[stepLen++] = i;
    }
}

int main()
{
    int i;
    while (1)
    {
        len = 0;
        while (scanf("%d", &arrOrigin[len]) > 0)
        {
            arr[len] = arrOrigin[len];
            ++len;
            if (getchar() == '\n')
                break;
        }
        if (len == 0)
            return 0;
        stepLen = 0;
        loop();
        for (i = 0; i < len; ++i)
        {
            if (i != 0)
                putchar(' ');
            printf("%d", arrOrigin[i]);
        }
        putchar('\n');
        for (i = 0; i < stepLen; ++i)
            printf("%d ", len - stepArr[i]);
        putchar('0');
        putchar('\n');
    }
    return 0;
}