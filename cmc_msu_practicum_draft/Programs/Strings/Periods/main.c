#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char a[1000002];
    fgets (a, 1000002, stdin);
    a[strlen( a) - 1] = '\0';
    int len_a = strlen(a), i, period, mark;
    for (period = 1; period < len_a; ++period) {
        mark = 1;
        for (i = period; i < len_a; ++i) {
            if (a[i] != a[i - period]) {
                mark = 0;
            }
        }
        if (mark) {
            printf("%d\t", period);
        }
    }
    printf("%d\t", len_a);
    return 0;
}
