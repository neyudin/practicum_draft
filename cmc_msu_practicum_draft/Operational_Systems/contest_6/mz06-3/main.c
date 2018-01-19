#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum
{
    NUM = 100
};

int
main(int argc, char *argv[])
{
    int numbers[NUM][2], n, m, seed;
    if (scanf("%d", &n) <= 0) {
        perror("scanning error");
        return 1;
    }
    for (int i = 0; i < n; ++i) {
        if (scanf("%d%d", &numbers[i][0], &numbers[i][1]) <= 0) {
            perror("scanning error");
            return 1;
        }
    }
    if (scanf("%d%d", &m, &seed) <= 0) {
        perror("scanning error");
        return 1;
    }
    srand(seed);
    for (int i = 0, value; i < m; ++i) {
        double dist = rand()/(RAND_MAX + 1.0);
        value = (int) (dist * NUM);
        for (int j = 0, sum = 0; j < n; ++j) {
            if ((sum += numbers[j][1]) > value) {
                printf("%d\n", numbers[j][0]);
                break;
            }
        }
    }
    return 0;
}