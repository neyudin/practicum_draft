#include <stdio.h>
#include <stdlib.h>

enum {ARRAY_SIZE = 1023};

int compare(const void *first, const void *second)
{
    if (*(double *)first > *(double *)second) {
        return -1;
    }
    if (*(double *)first < *(double *)second) {
        return 1;
    } else {
        return 0;
    }
}

int main(void)
{
    int N;
    if (scanf("%d", &N) == 0) {
        return 1;
    }
    double unsorted[ARRAY_SIZE], sorted[ARRAY_SIZE];
    for (int i = 0; i < N; ++i) {
        if (scanf("%lf", &unsorted[i]) == 0) {
            return 2;
        }
        sorted[i] = unsorted[i];
    }
    qsort(sorted, N, sizeof(sorted[0]), compare);
    for (int i = 0; i < N; ++i) {
        printf("%d %.10g %.10g\n", i + 1, unsorted[i], sorted[i]);
    }
    return 0;
}
