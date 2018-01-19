#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

enum
{
    NEG = 0,
    SQR = 1
};

int MODE = NEG;

int
neg(int a)
{
    return -a;
}

int
sqr(int a)
{
    return a * a;
}

void
hnd(int sig)
{
    if (sig == SIGUSR1) {
        MODE = NEG;
    }
    if (sig == SIGUSR2) {
        MODE = SQR;
    }
}

int
main(int argc, char **argv)
{
    int num;
    signal(SIGUSR1, hnd);
    signal(SIGUSR2, hnd);
    printf("%d\n", (int) getpid());
    fflush(stdout);
    while(scanf("%d", &num) > 0) {
        printf("%d\n", (MODE == NEG) ? neg(num) : sqr(num));
        fflush(stdout);
    }
    return 0;
}