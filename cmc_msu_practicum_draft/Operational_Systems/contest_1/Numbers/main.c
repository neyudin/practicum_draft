#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

enum {PATTERN_SIZE = 10};

int main(void)
{
    char path[PATH_MAX] = {0};
    if (fgets(path, sizeof(path), stdin) == NULL) {
        return 1;
    }
    path[strlen(path) - 1] = '\0';
    FILE *input = fopen(path, "r");
    if (input == NULL) {
        return 2;
    }
    unsigned pattern[PATTERN_SIZE] = {0};
    int c;
    while ((c = fgetc(input)) != EOF) {
        if ((c >= '0') && (c <= '9')) {
            ++pattern[c - '0'];
        }
    }
    fclose(input);
    for (int i = 0; i < PATTERN_SIZE; ++i) {
        printf("%d %u\n", i, pattern[i]);
    }
    return 0;
}
