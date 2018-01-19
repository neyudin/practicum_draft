#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char a[1000002], b[1000002], c[2000002], d[2000002];
    fgets (a, 1000002, stdin);
    a[strlen( a) - 1] = '\0';
    fgets (b, 1000002, stdin);
    b[strlen( b) - 1] = '\0';
    int len_a = strlen(a), len_b = strlen(b), j, index;
    int a_prefix[len_a + len_b + 1], b_prefix[len_a + len_b + 1];
    for (j = 0; j < len_a + len_b + 1; ++j) {
        a_prefix[j] = 0;
        b_prefix[j] = 0;
    }
    strcat(c, a);
    strcat(c, " ");
    strcat(c, b);
	for (j = 1; j < len_a + len_b + 1; ++j) {
        index = a_prefix[j - 1];
        while ((index > 0) && (c[j] != c[index])) {
            index = a_prefix[index - 1];
        }
        if (index == 0) {
            a_prefix[j] = 0;
        }
        if (c[j] == c[index]) {
            a_prefix[j] = index + 1;
        }
	}
    strcat(d, b);
    strcat(d, " ");
    strcat(d, a);
	for (j = 1; j < len_a + len_b + 1; ++j) {
        index = b_prefix[j - 1];
        while ((index > 0) && (d[j] != d[index])) {
            index = b_prefix[index - 1];
        }
        if (index == 0) {
            b_prefix[j] = 0;
        }
        if (d[j] == d[index]) {
            b_prefix[j] = index + 1;
        }
	}
    printf("%d\t%d", a_prefix[len_a + len_b], b_prefix[len_a + len_b]);
    return 0;
}
