#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int
myex(char *arg)
{
    if (!fork()) {
        execlp(arg, arg, (char *) NULL);
        exit(1);
    }
    int status;
    wait(&status);
    return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
}

int
main(int argc, char **argv)
{
    return !((!myex(argv[1]) || !myex(argv[2])) && !myex(argv[3]));
}