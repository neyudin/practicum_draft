#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char a[1000002], b[1000002];
    fgets (a, 1000002, stdin);
    a[strlen( a) - 1] = '\0';
    fgets (b, 1000002, stdin);
    b[strlen( b) - 1] = '\0';
    int len_a = strlen(a), len_b = strlen(b), i, pref_len, j, post_len, delta, prlm, polm;
    if (len_a > len_b)      i = len_b;
    else                    i = len_a;
    pref_len = 0;
    post_len = 0;
    prlm = 0;
    polm = 0;
    for (delta = 1; delta < i + 1; ++delta) {
        for (j = 0; j < delta; ++j) {
            if (a[j] == b[len_b + j - delta]) {
                ++pref_len;
            }
        }
        if ((pref_len > prlm) & (pref_len == delta)) {
            prlm = pref_len;
        }
        for (j = 0; j < delta; ++j) {
            if (b[j] == a[len_a + j - delta]) {
                ++post_len;
            }
        }
        if ((post_len > polm) & (post_len == delta)) {
            polm = post_len;
        }
        pref_len = 0;
        post_len = 0;
    }
    printf("%d\t%d", prlm, polm);
    return 0;
}






