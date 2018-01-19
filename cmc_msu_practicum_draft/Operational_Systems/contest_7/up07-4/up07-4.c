#include <stdio.h>
#include <stdlib.h>

enum
{
    SIZE = 4096,
    SLIDE = 22
};

int
main(int argc, char **argv)
{
    int c;
    unsigned begin, end, prev_up = 0xffffffff, result = 0;
    while (scanf("%x-%x", &begin, &end) > 1) {
        while ((c = getchar()) != '\n' && c != EOF) {}
        begin >>= SLIDE;
        end >>= SLIDE;
        result += end - begin;
        if (prev_up != begin) {
            ++result;
        }
        prev_up = end;
    }
    ++result;
    printf("%u\n", result * SIZE);
    return 0;
}