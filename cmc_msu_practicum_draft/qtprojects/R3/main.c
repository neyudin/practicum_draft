#include <stdio.h>
#include <stdlib.h>

int N = 0, K = 0, a[30] = {0}, b[30] = {0};

int main(void)
{
    int *k_arr, *tmp_arr, *tmp, tmp_n = 0, k_num, tmp_num;
    scanf("%d%d", &N, &K);
    k_arr = a;
    tmp_arr = b;
    *k_arr = 1;
    /**/int j, k = N;
    for (j = 0; j <= k; ++j) {
    N = j;
    K = j/2;/**/
    while (tmp_n != N) {
        ++tmp_n;
        *tmp_arr = 1;
        tmp_num = 0;
        while (tmp_num != tmp_n) {
            ++tmp_num;
            k_num = k_arr[tmp_num];
            k_num += k_arr[tmp_num - 1];
            tmp_arr[tmp_num] = k_num;
        }
            tmp_arr[tmp_num] = 1;
            tmp = k_arr;
            k_arr = tmp_arr;
            tmp_arr = tmp;
    }
    k_num = k_arr[K];
    //printf("%d\n", k_num);
    int i;
    //printf("(k - 1) string (0 index) is\n");
    for (i = 0; i < N; ++i) {
        printf("%d, ", k_arr[i]);
    }
    printf("1,\n");
    /**/}/**/
    return 0;
}

