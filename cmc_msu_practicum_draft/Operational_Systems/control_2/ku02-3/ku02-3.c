#include <stdio.h>
#include <stdlib.h>

enum
{
    A_MUL = 64,
    LINE_INFO_SIZE = 3,
    MASK_SIZE = 5,
    R_MASK = 4
};

typedef struct vector
{
    unsigned **v;
    int u;
    int a;
} vector;

int
store(vector *unit, FILE *file)
{
    if (unit->u == unit->a) {
        if (!(unit->a *= 2)) {
            unit->a = A_MUL;
        }
        unit->v = realloc(unit->v, unit->a * sizeof(*unit->v));
    }
    unit->v[unit->u++] = calloc(LINE_INFO_SIZE, sizeof(**unit->v));
    char mask[MASK_SIZE] = {0};
    if (fscanf(file, "%x-%x %s", &unit->v[unit->u - 1][0], &unit->v[unit->u - 1][1], mask) < 3) {
        return EOF;
    }
    if (mask[0] != '-') {
        unit->v[unit->u - 1][2] += R_MASK;
    }
    if (mask[1] != '-') {
        unit->v[unit->u - 1][2] += 2;
    }
    if (mask[2] != '-') {
        unit->v[unit->u - 1][2] += 1;
    }
    int c;
    while ((c = fgetc(file)) != '\n' && c != EOF) {}
    return c;
}

int
main(int argc, char **argv)
{
    vector *unit = calloc(1, sizeof(*unit));
    FILE *file = fopen(argv[1], "r");
    while (store(unit, file) != EOF) {}
    fclose(file);
    unsigned addr, op;
    while (scanf("%x %u", &addr, &op) == 2) {
        int i;
        for (i = 0; i < unit->u; ++i) {
            if (unit->v[i][0] <= addr && addr < unit->v[i][1]) {
                if (op) {
                    printf("%u\n", !(op & ~unit->v[i][2]));
                } else {
                    printf("1\n");
                }
                break;
            }
        }
        if (i == unit->u) {
            printf("0\n");
        }
    }
    for (int i = 0; i < unit->u; ++i) {
        free(unit->v[i]);
    }
    free(unit->v);
    free(unit);
    return 0;
}