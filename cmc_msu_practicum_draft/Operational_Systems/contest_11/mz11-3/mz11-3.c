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
rand_range(int low, int high)
{
    double dist = rand()/(RAND_MAX + 1.0);
    return (int) (dist * (high - low)) + low;
}

extern void operation(int * /*data*/, int /*ind1*/, int /*ind2*/, int /*value*/);
/*{
    if (ind1 != ind2) {
        int tmp1 = data[ind1] - value;
        int tmp2 = data[ind2] + value;

        data[ind1] = tmp1;
        data[ind2] = tmp2;
    }
}*/

int
main(int argc, char **argv)
{
    int count = strtol(argv[1], NULL, BASE);
    key_t key = strtol(argv[2], NULL, BASE);
    int nproc = strtol(argv[3], NULL, BASE);
    int iter_count = strtol(argv[4], NULL, BASE);
    int shmid = shmget(key, count * sizeof(count), IPC_EXCL | IPC_CREAT | SHM_PERMS);
    if (shmid == -1) {
        shmid = shmget(key, count * sizeof(count), 0);
    }
    int *addr = shmat(shmid, NULL, 0);
    int semid = semget(key, count, IPC_EXCL | IPC_CREAT | SEM_PERMS);
    if (semid == -1) {
        semid = semget(key, count, 0);
    }
    for (int i = 0; i < count; ++i) {
        if (scanf("%d", &addr[i]) < 1) {
            perror("scanf()");
            fflush(stderr);
        }
    }
    struct sembuf up[2] = {{0, 1, 0}, {1, 1, 0}};
    struct sembuf down[2] = {{0, -1, 0}, {1, -1, 0}};
    for (int i = 0; i < count; ++i) {
        up[0].sem_num = i;
        semop(semid, &up[0], 1);
    }
    for (int proci = 0; proci < nproc; ++proci) {
        if (!fork()) {
            srand(strtol(argv[5 + proci], NULL, BASE));
            for (int i = 0; i < iter_count; ++i) {
                int ind1 = rand_range(0, count);
                int ind2 = rand_range(0, count);
                int value = rand_range(0, BASE);
                if (ind1 == ind2) {
                    continue;
                }
                up[0].sem_num = ind1;
                up[1].sem_num = ind2;
                down[0].sem_num = ind1;
                down[1].sem_num = ind2;
                semop(semid, down, 2);
                operation(addr, ind1, ind2, value);
                semop(semid, up, 2);
            }
            return 0;
        }
    }
    for (int i = 0; i < nproc; ++i) {
        wait(NULL);
    }
    for (int i = 0; i < count; ++i) {
        printf("%d\n", addr[i]);
        fflush(stdout);
    }
    shmdt(addr);
    shmctl(shmid, IPC_RMID, NULL);
    for (int i = 0; i < count; ++i) {
        semctl(semid, i, IPC_RMID, NULL);
    }
    return 0;
}