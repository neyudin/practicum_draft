#include <stdio.h>
#include <stdlib.h>

double fun(int i) {
volatile double d[1] = {3.14};
volatile long int a[2];
a[i] = 1073741824;
return d[0] * a[i];
}

int main(void)
{
    for (int i = 0; i < 5; ++i)
        printf("%lf\n", fun(i));
    return 0;
}
