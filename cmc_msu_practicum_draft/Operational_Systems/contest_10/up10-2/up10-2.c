#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <math.h>

enum
{
    MAX_COUNT = 4
};

volatile int int_count = 0, last_prime = 0;

void
hnd1(int sig)
{
    if (sig == SIGINT) {
        if (++int_count == MAX_COUNT) {
            exit(0);
        } else {
            printf("%d\n", last_prime);
            fflush(stdout);
        }
        return;
    }
    exit(0);
}

int
main(int argc, char **argv)
{
    signal(SIGINT, hnd1);
    signal(SIGTERM, hnd1);
    int low, high;
    if (scanf("%d%d", &low, &high) < 2) {
        perror("scanf()");
        fflush(stderr);
        exit(0);
    }
    printf("%d\n", getpid());
    fflush(stdout);
    if (low < 3) {
        last_prime = 2;
    }
    for(int i = (low > 3) ? low : 3, flag = 1; i < high; ++i) {
        int bound = (int) sqrt(i) + 1;
        for (int j = 2; j <= bound; ++j) {
            if (i % j == 0) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            last_prime = i;
        }
        flag = 1;
    }
    printf("-1\n");
    fflush(stdout);
    return 0;
}