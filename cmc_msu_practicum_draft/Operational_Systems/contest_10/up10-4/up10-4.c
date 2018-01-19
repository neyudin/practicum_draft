#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int
read_to_buf_from_fd(int fd, void *buf, int buf_size)
{
    ssize_t already_read = 0;
    for (ssize_t dif = buf_size, count = 0; dif > 0; dif -= count) {
        count = read(fd, (char *) buf + already_read, dif);
        if (count < 0) {
            perror("reading error");
            fflush(stderr);
            return EOF;
        }
        if (!count) {
            return EOF;
        }
        already_read += count;
    }
    return already_read;
}

int
write_from_buf_to_fd(int fd, void *buf, int buf_size)
{
    ssize_t already_read = 0;
    for (ssize_t dif = buf_size, count = 0; dif > 0; dif -= count) {
        count = write(fd, (char *) buf + already_read, dif);
        if (count < 0) {
            perror("writing error");
            fflush(stderr);
            return EOF;
        }
        if (!count) {
            return EOF;
        }
        already_read += count;
    }
    return already_read;
}

int
main(int argc, char **argv)
{
    if (argc < 4) {
        perror("not enough arguments");
        fflush(stderr);
        return 0;
    }
    int pipefd[2] = {0};
    if (pipe(pipefd) == -1) {
        perror("pipe()");
        fflush(stderr);
        return 0;
    }
    int num = 0;
    if (!fork()) {
        close(pipefd[1]);
        int pid = 0;
        long long sum = 0;
        long long max = strtoll(argv[3], NULL, 10);
        read_to_buf_from_fd(pipefd[0], &pid, sizeof(pid));
        while(read_to_buf_from_fd(pipefd[0], &num, sizeof(num)) > 0) {
            sum += num;
            if (sum > max) {
                close(pipefd[0]);
                printf("-1\n");
                fflush(stdout);
                kill(SIGTERM, pid);
                exit(0);
            }
        }
        close(pipefd[0]);
        printf("%lld\n", sum);
        fflush(stdout);
    } else {
        if (!fork()) {
            if (!fork()) {
                close(pipefd[0]);
                FILE *f = fopen(argv[1], "r");
                int mod = strtol(argv[2], NULL, 10);
                num = getpid();
                write_from_buf_to_fd(pipefd[1], &num, sizeof(num));
                while (fscanf(f, "%d", &num) > 0) {
                    num = ((num % mod) * (num % mod)) % mod;
                    write_from_buf_to_fd(pipefd[1], &num, sizeof(num));
                }
                close(pipefd[1]);
                fclose(f);
            } else {
                close(pipefd[0]);
                close(pipefd[1]);
                wait(NULL);
            }
        } else {
            close(pipefd[0]);
            close(pipefd[1]);
            wait(NULL);
            wait(NULL);
            printf("0\n");
            fflush(stdout);
        }
    }
    return 0;
}