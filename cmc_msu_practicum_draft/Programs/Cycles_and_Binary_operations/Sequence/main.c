#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    long long N, A, B = 1, C, D = 1;
    scanf("%lld%lld", &N, &A);
    --N;
    while (N != 0) {
        scanf("%lld", &C);
        if(A < C) {
            ++B;
        }
        else {
            if (B > D) {
                    D = B;
                }
            B = 1;
        }
        A = C;
        --N;
    }
    if (B > D) {
            D = B;
    }
    printf("%lld\n", D);
    return 0;
}
