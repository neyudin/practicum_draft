#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int arrayreverse [10001];
    arrayreverse [0] = 1;
    int k;
    for (k = 1; arrayreverse [k - 1] != 0; ++k) {
        scanf("%d", &arrayreverse [k]);
    }
    for (k -= 2; k > 0; --k) {
        printf("%d\n", arrayreverse [k]);
    }
    return 0;
}
