#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(int argc, char **argv)
{
    int num;
    while (scanf("%d", &num) > 0) {
        if (fork()) {
            wait(NULL);
            printf("%d\n", num);
            break;
        }
    }   
    return 0;
}