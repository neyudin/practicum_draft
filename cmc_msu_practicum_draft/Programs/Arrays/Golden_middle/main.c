#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    int n;
    scanf("%d", &n);
    int num_array[n + 1];
    int count_triples = 0, b = 2, j, k;
    for (j = 1; j < n + 1; ++j) {
        scanf("%d", &num_array [j]);
    }
    for (k = 1 ; k < n + 1; ++k) {
        b = k + 1;
        for (j = k - 1; j > 0; --j ) {
            if (b < n + 1) {
                if (num_array [k] * 2 == num_array [b] + num_array [j])
                    ++count_triples;
            }
            ++b;
        }
    }
    printf("%d\n", count_triples);
    return 0;
}
