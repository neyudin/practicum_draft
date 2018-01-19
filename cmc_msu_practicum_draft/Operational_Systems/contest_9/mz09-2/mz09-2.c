#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int
main(int argc, char **argv)
{
    int pipefd[2];
    int fd;
    if (pipe(pipefd)) {
        perror("pipe()");
        return 0;
    }
    if (fork() == 0) {
        close(1);
        if (dup(pipefd[1]) == -1) {
            perror("dup() left pipe");
            return 0;
        }
        close(pipefd[0]);
        close(pipefd[1]);
        if (fork() == 0) {
            fd = open(argv[4], O_RDONLY);
            close(0);
            if (dup(fd) == -1) {
                perror("dup() cmd1");
                return 1;
            }
            close(fd);
            execlp(argv[1], argv[1], NULL);
            return 1;
        } else {
            int status;
            wait(&status);
            if (WIFEXITED(status) && !WEXITSTATUS(status)) {
                execlp(argv[2], argv[2], NULL);
            }
            return 0;
        }
    } else {
        close(0);
        if (dup(pipefd[0]) == -1) {
            perror("dup() right pipe");
            return 0;
        }
        close(pipefd[0]);
        close(pipefd[1]);
        fd = open(argv[5], O_WRONLY | O_CREAT | O_APPEND, 0644);
        close(1);
        if (dup(fd) == -1) {
            perror("dup() cmd3");
            return 0;
        }
        close(fd);
        if (fork() == 0) {
            execlp(argv[3], argv[3], NULL);
            return 0;
        }
        close(0);
        wait(NULL);
        wait(NULL);
        return 0;
    }
}