#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int
main(int argc, char **argv)
{
    key_t key = ftok(argv[0], '0');
    int id = semget(key, 2, IPC_CREAT | 0777);
    struct sembuf up1 = {0, 1, 0}, down1 = {0, -1, 0};
    struct sembuf up2 = {1, 1, 0}, down2 = {1, -1, 0};
    semop(id, &up1, 1);
    if (!fork()) {
        while(1) {
            semop(id, &down1, 1);
            printf("%d\n", getpid());
            fflush(stdout);
            semop(id, &up2, 1);
        }
    }
    while(1) {
        semop(id, &down2, 1);
        printf("%d\n", getpid());
        fflush(stdout);
        semop(id, &up1, 1);
    }
    return 0;
}