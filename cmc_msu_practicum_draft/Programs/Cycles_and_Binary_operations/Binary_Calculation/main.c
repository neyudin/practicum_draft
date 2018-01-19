#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    long long N, K, I = 1, S;
    S = 2;
    scanf("%lld%lld", &N, &K);
    if (K > 1) {
        while(K) {
            if (K&1)
                I *= S;
            S *= S;
            K >>= 1;
        }
    } else
        I = 2;
    printf("%lld\n", N%I);
    return 0;
}
