#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

enum
{
    BASE = 10,
    MSG_PERMS = 0666
};

struct msgbuf
{
    long mtype;
    int mtext;
};

int
main(int argc, char **argv)
{
    int limit = strtol(argv[1], NULL, BASE);
    struct msgbuf message;
    message.mtype = 1;
    message.mtext = 1;
    key_t key1 = ftok(argv[0], limit);
    key_t key2 = ftok(argv[0], limit + 1);
    int queue1 = msgget(key1, IPC_CREAT | MSG_PERMS);
    int queue2 = msgget(key2, IPC_CREAT | MSG_PERMS);
    if (!fork()) {
        while (message.mtext < limit) {
            msgrcv(queue1, &message, sizeof(message.mtext), 1, 0);
            if (message.mtext < limit) {
                printf("1 %d\n", message.mtext++);
                fflush(stdout);
            } else {
                break;
            }
            msgsnd(queue2, &message, sizeof(message.mtext), 0);
        }
        exit(0);
    }
    if (!fork()) {
        while (message.mtext < limit) {
            msgrcv(queue2, &message, sizeof(message.mtext), 1, 0);
            if (message.mtext < limit) {
                printf("2 %d\n", message.mtext++);
                fflush(stdout);
            } else {
                break;
            }
            msgsnd(queue1, &message, sizeof(message.mtext), 0);
        }
        exit(0);
    }
    msgsnd(queue1, &message, sizeof(message.mtext), 0);
    wait(NULL);
    wait(NULL);
    msgctl(queue1, IPC_RMID, 0);
    msgctl(queue2, IPC_RMID, 0);
    printf("Done\n");
    fflush(stdout);
    return 0;
}