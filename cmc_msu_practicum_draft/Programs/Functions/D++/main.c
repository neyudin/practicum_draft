#include <stdio.h>
#include <stdlib.h>
#include <math.h>
unsigned g(unsigned x)
{
    long long s = 0;
    if (x < 4){
        return x;
    }
    else {
        if ((unsigned long long) (cbrt(x) * 100000000) % 100000000 == 0) {
            return (unsigned) (cbrt(x)  *  cbrt(x));
        }
        else {

            unsigned i, k, index = 0;
            int max;
            for (i = 0; s <= x; i++) {
                s += 2 * i + 1;
            }
            max = x / (unsigned) cbrt((i - 1) * (i - 1)) - 30000;
            s = 0;
            if (max < 0)
                max = 0;
            for (k = max; k <= max + 30000; ++k) {
                for (i = 0; s <= k; i++) {
                    s += 2 * i + 1;
                }
                s = 0;
                if (x == k * (i - 1) ) {
                    index = k;
                    break;
                }
            }
            return index;
        }
    }
}
int main(void)
{
    unsigned x;
    scanf("%u", &x);
    printf("%u\n", g(x));
    return 0;
}
