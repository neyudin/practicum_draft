#include <stdio.h>
#include <stdlib.h>

int build(int *dispenser, int *choice, int index, int step, int grade, int previous) {
    int j, dev, mark;
    for (j = 0; j < 4; ++j) {
        mark = 1;
        dispenser[index] = previous * 10;
        dispenser[index] += choice[j];
        if (dispenser[index]) {
            for (dev = 3; dev < dispenser[index]/2 + 1; dev += (dev % 5 == 3 ? 4: 2)) {
                if (!(dispenser[index] % dev)) {
                    mark = 0;
                    break;
                }
            }
        }
        if ((step +  1 < grade) & mark) {
            index = build(dispenser, choice, index, (step + 1), grade, dispenser[index]);
        }
        if (mark & (step + 1 == grade)) {
            ++index;
        }
    }
    return index;
}

int main(void)
{
    int N;
    scanf("%d", &N);
    int i, index, number;
    int *main_choice = malloc(4 * sizeof(int)), *choice = malloc(4 * sizeof(int)), *dispenser = malloc(262144 * sizeof(int));
    main_choice[0] = 2;
    main_choice[1] = 3;
    main_choice[2] = 5;
    main_choice[3] = 7;
    choice[0] = 1;
    choice[1] = 3;
    choice[2] = 7;
    choice[3] = 9;
    for (i = 0, index = 0; i < 4; ++i) {
        number = main_choice[i];
        index = build(dispenser, choice, index, 1, N, number);
    }
    if (N > 1) {
        for(i = 0; i < index; ++i) {
            printf("%d\t", dispenser[i]);
        }
    } else {
        printf("2 3 5 7");
    }



    return 0;
}
