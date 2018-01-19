#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int
read_to_buf_from_fd(int fd, void *buf, int buf_size)
{
    lseek(fd, -buf_size, SEEK_CUR);
    for (ssize_t dif = buf_size, count = 0, already_read = 0; dif > 0; dif -= count) {
        count = read(fd, (char *) buf + already_read, dif);
        if (count < 0) {
            perror("reading error");
            lseek(fd, -already_read, SEEK_CUR);
            return already_read;
        }
        already_read += count;
    }
    lseek(fd, -buf_size, SEEK_CUR);
    return buf_size;
}

int
main(int argc, char **argv)
{
    if (argc < 2) {
        perror("not enough arguments");
        return 2;
    }
    int fd = open(argv[1], O_RDONLY);
    off_t filelength;
    if ((filelength = lseek(fd, 0, SEEK_END)) == 0) {
        close(fd);
        return 0;
    }
    while (filelength > 0) {
        unsigned short num;
        filelength -= read_to_buf_from_fd(fd, &num, sizeof(num));
        if (!num) {
            printf("0\n");
            continue;
        }
        double number, result = 1.0;
        for (int i = 0; i < num; ++i) {
            filelength -= read_to_buf_from_fd(fd, &number, sizeof(number));
            result *= number;
        }
        printf("%.10g\n", pow(result, 1.0/num));
    }
    close(fd);
    return 0;
}