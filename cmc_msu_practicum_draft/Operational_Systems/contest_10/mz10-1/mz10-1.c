#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>

int
myex(char *arg)
{
    int pid;
    if (!(pid = fork())) {
        execlp(arg, arg, NULL);
        exit(1);
    }
    int status;
    waitpid(pid, &status, 0);
    return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
}

int
read_file(char *filename, int mode)
{
    int count;
    char path[PATH_MAX] = {0};
    FILE *f = fopen(filename, "r");
    if ((count = fread(path, 1, PATH_MAX, f)) <= 0) {
        return -1;
    }
    path[count - 1] = '\0';
    fclose(f);
    if (!mode) {
        if (!fork()) {
            execlp(path, path, NULL);
            exit(1);
        }
    } else {
        return myex(path);
    }
    return 0;
}

int
main(int argc, char **argv)
{
    if (argc <= 2) {
        printf("0\n");
        fflush(stdout);
        return 0;
    }
    int num = strtol(argv[1], NULL, 10);
    int succ = 0;
    if (argc - 2 < num) {
        num = argc - 2;
    }
    for (int i = 0; i < num; ++i) {
        read_file(argv[i + 2], 0);
    }
    for (int i = 0; i < num; ++i) {
        int status;
        wait(&status);
        if (WIFEXITED(status) && !WEXITSTATUS(status)) {
            ++succ;
        }
    }
    for (int i = num + 2; i < argc; ++i) {
        if (read_file(argv[i], 1)) {
            continue;
        }
        ++succ;
    }
    printf("%d\n", succ);
    fflush(stdout);
    return 0;
}
