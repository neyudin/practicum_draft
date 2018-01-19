#include <stdio.h>
#include <stdlib.h>

int check_tree (int node, int end, int balance, int *array, int *lb, int *ub) {
    if (!array) {
        *lb = -1;
        *ub = 1;
        return 0;
    }
    if (!node) {
        if (2 * node + 1 < end) {

            if (array[node] > array[2 * node + 1]) {
                balance = -1;
                *lb = -1;
            } else {
                balance = 1;
                if (array[node] < array[2 * node + 1]) {
                    *ub = 1;
                } else {
                    *lb = 0;
                    *ub = 0;
                }
            }
            balance = check_tree(2 * node + 1, end, balance, array, lb, ub);
        } else {
            return 1;
        }
        if (2 * node + 2 < end) {
            if (((array[node] > array[2 * node + 1]) && (array[node] < array[2 * node + 2])) || ((array[node] < array[2 * node + 1]) && (array[node] > array[2 * node + 2]))) {
                return 0;
            } else {
                if (array[node] < array[2 * node + 2]) {
                    *ub += 1;
                }
                if (array[node] > array[2 * node + 2]) {
                    *lb -= 1;
                }
                balance = check_tree(2 * node + 2, end, balance, array, lb, ub);
            }
        }
    } else {
        if (2 * node +  1 < end) {

            if (array[node] > array[2 * node + 1]) {
                *lb -= 1;
            } else {
                if (array[node] < array[2 * node + 1]) {
                    *ub += 1;
                }
            }
            balance = check_tree(2 * node + 1, end, balance, array, lb, ub);
        }
        if (2 * node +  2 < end) {

            if (array[node] > array[2 * node + 2]) {
                *lb -= 1;
            } else {
                if (array[node] < array[2 * node + 2]) {
                    *ub += 1;
                }
            }
            balance = check_tree(2 * node + 2, end, balance, array, lb, ub);
        }
    }
    return balance;
}

int main(void)
{
    int *multitude = malloc(4194304);
    FILE *input = fopen("input.bin", "rb");
    int sz = fread(multitude, sizeof(int), 4194304/sizeof(int), input);
    fclose(input);
    int j, mark, i, lb, ub;
    i = 0, j = 0;
    lb = 0;
    ub = 0;
    mark = check_tree(i, sz, j, multitude, &lb, &ub);
    if ((lb == 0) && (ub == 0)) {
        mark = 1;
    }
    if (!lb && ub) {
        mark = 1;
    }
    if (lb && !ub) {
        mark = -1;
    }
    if ((lb < 0) && (ub > 0)) {
        mark = 0;
    }
    if (sz == 0) {
            mark = 0;
    }
    FILE *output = fopen("output.bin", "wb");
    switch (mark) {
        case (-1) : {fwrite(&mark, sizeof(int), 1, output); break;}
        case (1) : {fwrite(&mark, sizeof(int), 1, output); break;}
        case (0) : {fwrite(&mark, sizeof(int), 1, output); break;}
        default : {break;}
    }
    fclose(output);
    return 0;
}

