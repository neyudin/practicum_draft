#include <stdio.h>
#include <stdlib.h>
#include "rand.h"

enum
{
    ARGC = 5,
    BASE = 10
};

int
main(int argc, char *argv[])
{
    if (argc < ARGC) {
        perror("not enough arguments");
        return 2;
    }
    int count = strtol(argv[1], NULL, BASE);
    int low = strtol(argv[2], NULL, BASE);
    int high = strtol(argv[3], NULL, BASE);
    srand(strtol(argv[4], NULL, BASE));
    for (int i = 0; i < count; ++i) {
        printf("%d\n", rand_range(low, high));
    }
    return 0;
}