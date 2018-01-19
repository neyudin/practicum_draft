#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int N, A, S, X;
    scanf("%d\n", &N);
    X = N;
    --N;
    S = 0;
    while (N) {
        scanf("%d\n", &A);
        S ^= A;
        --N;
    }
    scanf("%d", &A);
    S ^= A;
    printf("%d\n", S);
    return 0;
}
