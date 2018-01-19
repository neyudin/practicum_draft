#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(int argc, char **argv)
{
    printf("1");
    fflush(stdout);
    if (!fork()) {
        printf("2");
    }
    wait(NULL);
    printf("3");
    return 0;
}