#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

enum
{
    SUCC_NUM = 3
};

int
main(int argc, char **argv)
{
    int pipefd[2] = {0};
    time_t buf = 0;
    struct tm *currenttime;
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 2;
    }
    if (!fork()) {
        if (!fork()) {
            if (!fork()) {
                close(pipefd[1]);
                if (read(pipefd[0], &buf, sizeof(buf)) != sizeof(buf)) {
                    perror("read");
                }
                currenttime = localtime(&buf);
                printf("S:%02d\n", currenttime->tm_sec);
                close(pipefd[0]);
            } else {
                close(pipefd[1]);
                wait(NULL);
                if (read(pipefd[0], &buf, sizeof(buf)) != sizeof(buf)) {
                    perror("read");
                }
                currenttime = localtime(&buf);
                printf("M:%02d\n", currenttime->tm_min);
                close(pipefd[0]);
            }
        } else {
            close(pipefd[1]);
            wait(NULL);
            if (read(pipefd[0], &buf, sizeof(buf)) != sizeof(buf)) {
                perror("read");
            }
            currenttime = localtime(&buf);
            printf("H:%02d\n", currenttime->tm_hour);
            close(pipefd[0]);
        }
    } else {
        close(pipefd[0]);
        buf = time(NULL);
        for (int i = 0; i < SUCC_NUM; ++i) {
            if (write(pipefd[1], &buf, sizeof(buf)) != sizeof(buf)) {
                perror("write");
            }
        }
        close(pipefd[1]);
        wait(NULL);
    }
    return 0;
}