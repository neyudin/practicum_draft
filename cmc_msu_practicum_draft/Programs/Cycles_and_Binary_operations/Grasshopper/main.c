#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(void)
{
   int x, y, n;
    scanf("%d%d", &x, &y);
    x = abs(x);
    y = abs(y);
    if (x < y)
        if ( (y %2 == 0) ^ (x %2 == 0) )
            n = 2*y + 1;
        else
            n = y*2;
    else
        if ( (y %2 == 0) ^ (x %2 == 0) )
            n = 2*x +1;
        else
            n = x*2;
    if ( abs(x - y) %2 == 1 )
        n -= 2;
    printf("%d\n", n);
    return 0;
}
