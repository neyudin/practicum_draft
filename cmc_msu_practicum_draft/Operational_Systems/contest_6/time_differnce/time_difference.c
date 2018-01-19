#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <fcntl.h>
#include <time.h>

enum
{
    BUF_SIZE = 1002
};

struct MyFile
{
    int fd;
    int size;
    char *buf;

    int used;
    ssize_t count;
    int iseof;
};

int
mygetc(struct MyFile *f)
{
    if (f->iseof) {
        return EOF;
    }
    if (f->used >= f->size) {
        f->used = 0;
    }
    f->count = read(f->fd, f->buf + f->used, 1);
    if (!f->count) {
        f->iseof = 1;
        return EOF;
    }
    f->used += f->count;
    return (unsigned char) f->buf[f->used - 1];
}

int
parse_time(struct MyFile *file, char *timeline)
{
    int c;
    while ((c = mygetc(file)) != '\n' && c != EOF) {
        *timeline++ = c;
    }
    *timeline = '\0';
    if (file->iseof) {
        return -1;
    }
    return 0;
}

int
main(int argc, char *argv[])
{
    struct MyFile file;
    memset(&file, 0, sizeof(file));
    file.fd = open(argv[1], O_RDONLY);
    file.size = BUF_SIZE;
    file.buf = calloc(1, BUF_SIZE);
    char timeline[BUF_SIZE] = {0};
    struct tm current_time;
    memset(&current_time, 0, sizeof(current_time));
    time_t prev, cur;
    int prev_flag = 0;
    while (!parse_time(&file, timeline)) {
        sscanf(timeline, "%d/%d/%d %d:%d:%d", &current_time.tm_year, &current_time.tm_mon,
            &current_time.tm_mday, &current_time.tm_hour, &current_time.tm_min,
            &current_time.tm_sec);
        current_time.tm_year -= 1900;
        current_time.tm_mon -= 1;
        current_time.tm_isdst = -1;
        cur = mktime(&current_time);
        if (prev_flag) {
            printf("%ld\n", cur - prev);
        }
        prev = cur;
        prev_flag = 1;
    }
    if (close(file.fd)) {
        perror("closing error");
        return 2;
    }
    free(file.buf);
    return 0;
}