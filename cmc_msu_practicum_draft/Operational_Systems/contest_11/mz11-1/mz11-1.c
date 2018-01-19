#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <ctype.h>
#include <string.h>

int pids[2] = {0};
volatile int state = 0;
volatile int count = 0;
unsigned char *addr = NULL;
FILE *f = NULL;

enum
{
    SIZE = 1002,
    PERMS = 0644,
    BASE = 10
};

void
hnd_child2(int sig)
{
    if (sig == SIGUSR2) {
        exit(0);
    }
    int linesize = strlen(addr) - 1;
    while(linesize >= 0 && isspace(addr[linesize])) {
        --linesize;
    }
    printf("%d\n", ++linesize);
    fflush(stdout);
    kill(getppid(), SIGUSR1);
}

void
hnd_child1(int sig)
{
    if (fgets(addr, SIZE, f)) {
        ++count;
        kill(getppid(), SIGUSR1);
    } else {
        sprintf(addr, "%d\n", count);
        kill(getppid(), SIGUSR2);
        fclose(f);
        exit(0);
    }
}

void
hnd_parent(int sig)
{
    if (sig == SIGUSR2) {
        printf("%d\n", (int) strtol(addr, NULL, BASE));
        fflush(stdout);
        kill(pids[1], SIGUSR2);
    }
    kill(pids[++state % 2], SIGUSR1);
}

int
main(int argc, char **argv)
{
    key_t key = strtol(argv[1], NULL, BASE);
    int id = shmget(key, SIZE, IPC_EXCL | IPC_CREAT | PERMS);
    if (id == -1) {
        id = shmget(key, SIZE, 0);
    }
    addr = shmat(id, NULL, 0);
    signal(SIGUSR1, hnd_child1);
    f = fopen(argv[2], "r");
    if (!(pids[0] = fork())) {
        while (1) {
            usleep(1);
        }
        return 0;
    }
    fclose(f);
    signal(SIGUSR1, hnd_child2);
    signal(SIGUSR2, hnd_child2);
    if (!(pids[1] = fork())) {
        while (1) {
            usleep(1);
        }
        return 0;
    }
    signal(SIGUSR1, hnd_parent);
    signal(SIGUSR2, hnd_parent);
    kill(pids[0], SIGUSR1);
    wait(NULL);
    wait(NULL);
    shmdt(addr);
    shmctl(id, IPC_RMID, NULL);
    return 0;
}