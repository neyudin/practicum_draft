#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
    int c;
    unsigned begin, end, sum = 0;
    while (scanf("%x-%x", &begin, &end) > 1) {
        while ((c = fgetc()) != '\n' && c != EOF) {}
        sum += end - begin;
    }
    printf("%u\n", sum);
    return 0;
}