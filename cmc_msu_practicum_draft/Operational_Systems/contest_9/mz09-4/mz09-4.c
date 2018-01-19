#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int buf = 0, check = 0, state = 0;
int childpid[2] = {0};
FILE *fpipe[2] = {0};

void
hnd1(int sig)
{
    if (fscanf(fpipe[0], "%d", &buf) > 0) {
        if (buf > 0 && buf < check) {
            if (sig  == SIGUSR1) {
                printf("1 %d\n", buf);
                fflush(stdout);
                fprintf(fpipe[1], "%d ", ++buf);
                fflush(fpipe[1]);
                kill(childpid[1], SIGUSR2);
            } else {
                printf("2 %d\n", buf);
                fflush(stdout);
                fprintf(fpipe[1], "%d ", ++buf);
                fflush(fpipe[1]);
                kill(childpid[0], SIGUSR1);
            }
        }
    }
}

void
hnd2(int sig)
{
    ++state;
}

int
main(int argc, char **argv)
{
    if (argc < 2) {
        perror("not enough arguments");
        return 2;
    }
    int pipefd[2] = {0};
    if (pipe(pipefd) == -1) {
        perror("pipe()");
        return 4;
    }
    signal(SIGUSR1, hnd1);
    signal(SIGUSR2, hnd1);
    fpipe[0] = fdopen(pipefd[0], "r");
    fpipe[1] = fdopen(pipefd[1], "w");
    buf = 0;
    check = strtol(argv[1], NULL, 10);
    if ((childpid[0] = fork()) != 0) {
        childpid[1] = fork();
    } else {
        if (fscanf(fpipe[0], "%d ", &childpid[1]) <= 0) {
            perror("fscanf");
            return 6;
        }
        kill(getppid(), SIGUSR1);
        while (buf < check) {
            usleep(0);
        }
        fclose(fpipe[0]);
        close(pipefd[0]);
        fclose(fpipe[1]);
        close(pipefd[1]);
        return 0;
    }
    if (childpid[1] != 0) {
        signal(SIGUSR1, hnd2);
        fclose(fpipe[0]);
        close(pipefd[0]);
        fprintf(fpipe[1], "%d %d ", childpid[1], ++buf);
        fflush(fpipe[1]);
        fclose(fpipe[1]);
        close(pipefd[1]);
        while (state < 1) {
            usleep(10);
        }
        kill(childpid[0], SIGUSR1);
        wait(NULL);
        wait(NULL);
        printf("Done\n");
        fflush(stdout);
    } else {
        while (buf < check && check != 1) {
            usleep(0);
        }
        fclose(fpipe[0]);
        close(pipefd[0]);
        fclose(fpipe[1]);
        close(pipefd[1]);
    }
    return 0;
}