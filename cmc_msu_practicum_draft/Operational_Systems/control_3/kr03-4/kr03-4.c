#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

enum
{
    BYTE = 8
};

FILE *file = NULL;
volatile int c = 0, count = 0, pid = 0;

void
print_hnd(int sig, siginfo_t *siginfo, void *ptr)
{
    if (sig == SIGIO) {
        exit(0);
    }
    if (sig == SIGUSR1) {
        c <<= 1;
    } else {
        c = (c << 1) | 1;
    }
    if (++count == BYTE) {
        count = 0;
        printf("%c", c);
        fflush(stdout);
        c = 0;
    }
    kill(siginfo->si_pid, SIGALRM);
}

void
scan_hnd(int sig, siginfo_t *siginfo, void *ptr)
{
    int targetpid = 0;
    if (siginfo->si_pid == getpid()) {
        targetpid = pid;
    } else {
        targetpid = siginfo->si_pid;
    }
    if (!count++) {
        c = fgetc(file);
        if (c == EOF) {
            kill(targetpid, SIGIO);
            fclose(file);
            exit(0);
        }
    }
    if ((c & (1 << (BYTE - count)))) {
        kill(targetpid, SIGUSR2);
    } else {
        kill(targetpid, SIGUSR1);
    }
    if (count == BYTE) {
        count = 0;
        c = 0;
    }
    return;
}

int
main(int argc, char **argv)
{
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_sigaction = print_hnd;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act, NULL);
    sigaction(SIGUSR2, &act, NULL);
    sigaction(SIGIO, &act, NULL);
    act.sa_sigaction = scan_hnd;
    sigaction(SIGALRM, &act, NULL);
    if (!(pid = fork())) {
        while (1) {
            usleep(1);
        }
    } else {
        if (!fork()) {
            file = fopen(argv[1], "r");
            kill(getpid(), SIGALRM);
            while (1) {
                usleep(1);
            }
        } else {
            wait(NULL);
            wait(NULL);
        }
    }
    return 0;
}