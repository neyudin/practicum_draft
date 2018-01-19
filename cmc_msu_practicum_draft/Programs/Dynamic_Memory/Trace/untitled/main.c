#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define LONG_LONG_MIN (-9223372036854775807LL - 1)

int main(void)
{

    int N, i, j, size = 0;
    long long trace = 0, max_trace = LONG_LONG_MIN;
    scanf("%d", &N);
    int **M_pointers = NULL;
    int **MAX_M_pointers = NULL;
    for (i = 0; i < N; ++i) {
        int k, Ni;
        scanf("%d", &Ni);
        M_pointers = (int **) malloc(sizeof(int *) * Ni);
        for (k = 0; k < Ni; ++k) {
            M_pointers[k] = (int *) malloc(sizeof(int) * Ni);
        }
        for (j = 0; j < Ni; ++j) {
            for (k = 0; k < Ni; ++k) {
                scanf("%d", &M_pointers[j][k]);
                if (j == k) {
                    trace += M_pointers[j][k];
                }
            }
        }
        if (trace > max_trace) {
            max_trace = trace;
            free(MAX_M_pointers);
            MAX_M_pointers = M_pointers;
            size = Ni;
        } else {
            free(M_pointers);
        }
        trace = 0;
    }
    for (i = 0; i < size; ++i) {
        for (j = 0; j < size; ++j) {
            printf("%d\t", MAX_M_pointers[i][j]);
        }
        printf("\n");
    }
    return 0;
}
