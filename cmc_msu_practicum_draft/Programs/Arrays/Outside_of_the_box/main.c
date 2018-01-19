#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n;
    scanf("%d\n", &n);
    int array_of_boxes [n][2];
    int i, j, sp = 0;
    for (i = 0; i < 2; ++i) {
        for (j = 0; j < n; ++j) {
            scanf("%d", &array_of_boxes [j][i]);
        }
    }
    for (j = 0; j < n; ++j)
        if (array_of_boxes [j][0] >  array_of_boxes [j][1])
            sp += array_of_boxes [j][0];
        else
            sp += array_of_boxes [j][1];
    printf("%d\n", sp);
    return 0;
}

