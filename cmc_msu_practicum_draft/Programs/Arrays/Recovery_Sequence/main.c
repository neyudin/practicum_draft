#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    int n, i, j, sum_rev = 0, sup = 0, mark = 0, x, z, sequencesum = 0;
    scanf("%d", &n);
    int sequence [n], recovery [n], result [n];
    for (i = 0; i < n; ++i) {
        scanf("%d", &sequence [i]);
        recovery [i] = i + 1;
        sup += sequence [i];
        if (sequence [i] < 0) {
            mark = 1;
        }
    }
    j = n - 1;
    for (i = 0; i < n; ++i) {
        if (sequence [i] == 0) {
            result [i] = recovery [j];
            sequencesum += result [i];
            recovery [j] = 0;
            for (j = n - 1; recovery[j] == 0; --j)
            {continue;
            }
        } else {
            z = sequence [i] + 1;
            for (x = n - 1; z != 0; --x) {
                if (recovery [x] != 0) {
                    --z;
                }
            }
            ++x;
            result [i] = recovery [x];
            sequencesum += result [i];
            recovery [x] = 0;
        }
    }
    for (i = 0; i < n; ++i) {
        for (j = i + 1; j < n; ++j) {
            if (result[i] > result[j]) {
                ++sum_rev;
            }
        }
    }
    if ((mark) || (sup > n * (n - 1)/2) || (sum_rev > n * (n - 1)/2) || (sequencesum != (1 + n) * n/2))  /*control of correct*/
        printf("%d", -1);
    else
        for (i = 0; i < n; ++i)
            printf("%d\t", result [i]);
    return 0;
}
