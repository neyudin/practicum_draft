#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int
main(int argc, char **argv)
{
    int pipefd[2] = {0};
    int prev_in_fd = 0;
    for (int i = 1; i < argc; ++i) {
        if (pipe(pipefd) == -1) {
            perror("pipe()");
            exit(0);
        }
        if (!fork()) {
            if (i != 1) {
                close(0);
                if (dup(prev_in_fd) == -1) {
                    perror("dup()");
                    exit(0);
                }
                close(prev_in_fd);
            }
            if (i != argc - 1) {
                close(1);
                if (dup(pipefd[1]) == -1) {
                    perror("dup()");
                    exit(0);
                }
            }
            close(pipefd[0]);
            close(pipefd[1]);
            execlp(argv[i], argv[i], NULL);
            close(0);
            close(1);
            exit(0);
        } else {
            close(pipefd[1]);
            if (i != 1) {
                close(prev_in_fd);
            }
            prev_in_fd = pipefd[0];
        }
    }
    close(pipefd[0]);
    for (int i = 1; i < argc; ++i) {
        wait(NULL);
    }
    return 0;
}