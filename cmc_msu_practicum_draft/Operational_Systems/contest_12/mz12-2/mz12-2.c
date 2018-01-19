#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

enum
{
    MSG_PERMS = 0666
};

struct msgbuf
{
    long mtype;
    char mtext[1];
};

int
main(int argc, char **argv)
{
    struct msgbuf message;
    message.mtype = 1;
    message.mtext[0] = 'a';
    int num;
    key_t key1 = ftok(argv[0], MSG_PERMS);
    int queue1 = msgget(key1, IPC_CREAT | MSG_PERMS);
    setvbuf(stdin, NULL, _IONBF, 0);
    if (!fork()) {
        while (1) {
            msgrcv(queue1, &message, sizeof(message.mtext), 1, 0);
            message.mtype = 2;
            if (scanf("%d", &num) < 1) {
                msgsnd(queue1, &message, sizeof(message.mtext), 0);
                break;
            }
            printf("1 %d\n", num);
            fflush(stdout);
            msgsnd(queue1, &message, sizeof(message.mtext), 0);
        }
        exit(0);
    }
    if (!fork()) {
        while (1) {
            msgrcv(queue1, &message, sizeof(message.mtext), 2, 0);
            message.mtype = 1;
            if (scanf("%d", &num) < 1) {
                msgsnd(queue1, &message, sizeof(message.mtext), 0);
                break;
            }
            printf("2 %d\n", num);
            fflush(stdout);
            msgsnd(queue1, &message, sizeof(message.mtext), 0);
        }
        exit(0);
    }
    msgsnd(queue1, &message, sizeof(message.mtext), 0);
    wait(NULL);
    wait(NULL);
    msgctl(queue1, IPC_RMID, 0);
    return 0;
}