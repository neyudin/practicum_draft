#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int combination (int index) {
    int k, m, j, x = (int)pow(2, index), compare_that = 0, i = 0;
    int num [index], multit [index][x], multsum[x];
    for (k = 0; k < index; ++k) {
        scanf("%d", &num [k]);
    }
    for (k = 0; k < x; ++k) {
        multsum [k] = 0;
        for ( m = 0; m < index; ++m ) {
            if (k & (1 << m)){
                multit [m][k] = num [m];
                multsum [k] += num [m];
            } else {
                multit [m][k] = -1;
            }
        }
    }
    for (k = 0; k < x - 1; ++k) {
        for (m = k + 1; m < x; ++m) {
            if ((multsum[k] == multsum[m]) && (multsum[m] > compare_that)) {
                for (j = 0; j < index; ++j) {
                    if ((multit[j][m] == -1) || (multit[j][k] == -1)) {
                        ++i;
                    }
                }
                if (i == index) {
                    compare_that = multsum[m];
                }
                i = 0;
            }
        }
    }
    return compare_that;
}

int main(void)
{
    int n;
    scanf("%d", &n);
    printf("%d\n", combination(n));
    return 0;

}
