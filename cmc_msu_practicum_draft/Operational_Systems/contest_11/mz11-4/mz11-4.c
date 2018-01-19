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

extern void operation(int * , int , int , int );

extern int summ(const int * , int );

int
main(int argc, char **argv)
{
    int count = strtol(argv[1], NULL, BASE);
    key_t key = strtol(argv[2], NULL, BASE);
    int shmid = shmget(key, count * sizeof(count), IPC_EXCL | IPC_CREAT | SHM_PERMS);
    if (shmid == -1) {
        shmid = shmget(key, count * sizeof(count), 0);
    }
    int *addr = shmat(shmid, NULL, 0);
    int semid = semget(key, count + 2, IPC_EXCL | IPC_CREAT | SEM_PERMS);
    if (semid == -1) {
        semid = semget(key, count + 2, 0);
    }
    for (int i = 0; i < count; ++i) {
        if (scanf("%d", &addr[i]) < 1) {
            perror("scanf()");
            fflush(stderr);
        }
    }
    struct sembuf *up_all;
    up_all = calloc(count, sizeof(*up_all));
    struct sembuf *down_all;
    down_all = calloc(count, sizeof(*down_all));
    for (int i = 0; i < count; ++i) {
        up_all[i].sem_num = i;
        up_all[i].sem_op = 1;
        up_all[i].sem_flg = 0;
        down_all[i].sem_num = i;
        down_all[i].sem_op = -1;
        down_all[i].sem_flg = 0;
    }
    semop(semid, up_all, count);
    if (!fork()) {
        //writer
        struct sembuf up[] = {{0, 1, 0}, {1, 1, 0}};
        struct sembuf down[] = {{0, -1, 0}, {1, -1, 0}};
        srand(strtol(argv[4], NULL, BASE));
        int iter_count = strtol(argv[3], NULL, BASE);
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
        struct sembuf up1 = {count, 1, 0};
        semop(semid, &up1, 1);
        return 0;
    }
    if (!fork()) {
        //reader
        long long sum = 0;
        int iter_count = strtol(argv[3], NULL, BASE);
        for (int i = 0; i < iter_count; ++i) {
            semop(semid, down_all, count);
            sum += summ(addr, count);
            semop(semid, up_all, count);
        }
        printf("%lld\n", sum);
        struct sembuf up2 = {count + 1, 1, 0};
        semop(semid, &up2, 1);
        return 0;
    }
    struct sembuf down[] = {{count, -1, 0}, {count + 1, -1, 0}};
    semop(semid, down, 2);
    free(up_all);
    free(down_all);
    shmdt(addr);
    shmctl(shmid, IPC_RMID, NULL);
    for (int i = 0; i < count + 2; ++i) {
        semctl(semid, i, IPC_RMID, NULL);
    }
    return 0;
}