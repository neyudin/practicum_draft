#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    unsigned int A = 0, AT = 0, aij = 0;
    int K = 16, j = 0;
    scanf("%x", &A);
    while (K) {
        aij = A % 2;
        if (aij != 0)
            aij = aij << j;
        AT += aij;
        --K;
        A = A >> 1;
        if (K % 4 == 0)
            j -= 11;
        else
            j += 4;
    }
    aij = 0;
    printf("%04x\n", AT);
    return 0;
}
