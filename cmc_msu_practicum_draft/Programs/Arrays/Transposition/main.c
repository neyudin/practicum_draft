#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
int main(void)
{
    int n, i, c;
    scanf("%d\n", &n);
    int transposition [n + 1], natura [n + 1], index [n + 1];
    for (i = 1; i <= n; ++i) {
        scanf("%d", &natura [i]);
        index [i] = natura [i];
    }
    for (c = 0; c < 2; ++c) {
        for (i = 1; i <= n; ++i) {
            transposition [i] = index [natura [i]];
        }
        for (i = 1; i <= n; ++i) {
            index [i] = transposition [i];
        }
    }
    for (i = 1; i <= n; ++i)
    printf("%d\t", transposition [i]);
    return 0;
}
/*1 2 3 > 3 1 2 > 2 3 1 > 1 2 3
  1 2 3 > 1 3 2 > 1 2 3 > 1 3 2
*/
