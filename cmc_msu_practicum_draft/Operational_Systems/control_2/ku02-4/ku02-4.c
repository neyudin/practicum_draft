#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

void
write_from_buf_to_fd(int fd, void *buf, int buf_size)
{
    for (ssize_t dif = buf_size, count = 0, already_read = 0; dif > 0; dif -= count) {
        count = write(fd, (char *) buf + already_read, dif);
        if (count < 0) {
            perror("writing error");
            return;
        }
        already_read += count;
    }
}

int
main(int argc, char **argv)
{
    int proc_num = strtol(argv[1], NULL, 10);
    int begin = strtol(argv[3], NULL, 10);
    int dif = strtol(argv[4], NULL, 10);
    int num = strtol(argv[5], NULL, 10);
    pid_t pid = 1;
    int pid_id = 0;
    for (int i = 0; i < proc_num; ++i) {
        if(!(pid = fork())) {
            pid_id = i;
            break;
        }
    }
    if (pid) {
        for (int i = 0; i < proc_num; ++i) {
            wait(NULL);
        }
    } else {
        int fd = open(argv[2], O_WRONLY);
        if (fd == -1) {
            fd = creat(argv[2], 00644);
        }
        for (int i = 0, cur = begin + pid_id * dif; i < num; ++i) {
            lseek(fd, (pid_id + proc_num * i) * sizeof(cur), SEEK_SET);
            write_from_buf_to_fd(fd, &cur, sizeof(cur));
            cur += proc_num * dif;
        }
        close(fd);
    }
    return 0;
}