#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

enum
{
    SEM_PERMS = 0755,
    SHM_PERMS = 0644,
    BASE = 10
};

int
main(int argc, char **argv)
{
    int nproc = strtol(argv[1], NULL, BASE);
    key_t key = strtol(argv[2], NULL, BASE);
    int maxval = strtol(argv[3], NULL, BASE);
    int shmid = shmget(key, sizeof(maxval), IPC_EXCL | IPC_CREAT | SHM_PERMS);
    if (shmid == -1) {
        shmid = shmget(key, sizeof(maxval), 0);
    }
    int *addr = shmat(shmid, NULL, 0);
    int semid = semget(key, nproc, IPC_EXCL | IPC_CREAT | SEM_PERMS);
    if (semid == -1) {
        semid = semget(key, nproc, 0);
    }
    struct sembuf *up;
    up = calloc(nproc, sizeof(*up));
    struct sembuf *down;
    down = calloc(nproc, sizeof(*down));
    for (int i = 0; i < nproc; ++i) {
        up[i].sem_num = i;
        up[i].sem_op = 1;
        up[i].sem_flg = 0;
        down[i].sem_num = i;
        down[i].sem_op = -1;
        down[i].sem_flg = 0;
    }
    int proci;
    semop(semid, &up[0], 1);
    for (proci = 0, *addr = 0; proci < nproc; ++proci) {
        if (!fork()) {
            while (*addr <= maxval) {
                semop(semid, &down[proci], 1);
                if (*addr > maxval) {
                    break;
                }
                printf("%d: %d\n", proci, (*addr)++);
                fflush(stdout);
                if (*addr > maxval) {
                    break;
                }
                semop(semid, &up[((*addr) * (*addr)) % nproc], 1);
            }
            semop(semid, &up[(proci + 1) % nproc], 1);
            return 0;
        }
    }
    for (int i = 0; i < nproc; ++i) {
        wait(NULL);
    }
    shmdt(addr);
    shmctl(shmid, IPC_RMID, NULL);
    free(up);
    free(down);
    for (int i = 0; i < nproc; ++i) {
        semctl(semid, i, IPC_RMID, NULL);
    }
    return 0;
}