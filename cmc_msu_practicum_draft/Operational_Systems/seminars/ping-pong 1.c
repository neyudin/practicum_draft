#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int
main(int argc, char **argv)
{
    key_t key = ftok(argv[0], '0');
    int id = semget(key, 2, IPC_CREAT | IPC_EXCL | 0777);
    struct sembuf up[] = {{0, 1, 0}, {1, 1, 0}};
    struct sembuf down[] = {{0, -1, 0}, {1, -1, 0}};
    int number;
    if (id == -1) {
        number = 1;
        id = semget(key, 2, 0);
    } else {
        number = 0;
        semop(id, &up[0], 1);
    }
    while(1) {
        semop(id, &down[number], 1);
        printf("%d\n", getpid());
        fflush(stdout);
        semop(id, &up[1 - number], 1);
    }
    return 0;
}