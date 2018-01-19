#include <stdio.h>
#include <stdlib.h>

int symmetry (int n, int sumx) {
    int x, y;
    scanf("%d%d", &x, &y);
    if (x) {
        sumx += x + y;
    }
    --n;
    if (n)
        sumx = symmetry(n, sumx);

    return sumx;
}

int main(void)
{
    int x, sx = 0;
    scanf("%d", &x);
    x = symmetry(x, sx);
    if (x % 2 == 0)
        printf("Yes\n");
    else
        printf("No\n");
    return 0;
}
