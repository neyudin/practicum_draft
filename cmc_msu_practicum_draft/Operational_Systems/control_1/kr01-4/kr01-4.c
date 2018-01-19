#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

enum
{
    ARG_COUNT = 3
};

struct info
{
    unsigned short size;
    long long offset;
    long long structsize;
    long long number;
    long long totalsize;
};

void
read_to_buf(int fd, void *buf, int buf_size)
{
    for (ssize_t dif = buf_size, count = 0, already_read = 0; dif > 0; dif -= count) {
        count = read(fd, (char *) buf + already_read, dif);
        if (count < 0) {
            perror("reading error");
            return;
        }
        already_read += count;
    }
}

int
main(int argc, char *argv[])
{
    if (argc < ARG_COUNT) {
        perror("not enough arguments");
    }
    int fd = open(argv[1], O_RDONLY);
    if (lseek(fd, 0, SEEK_END) <= 0) {
        printf("0\n0\n");
        return 0;
    }
    if (lseek(fd, strtoll(argv[2], NULL, 10), SEEK_SET) < 0) {
        perror("seeking error");
    }
    struct info *node = calloc(1, sizeof(*node));
    for (node->offset = 1; node->offset; ++node->number) {
        read_to_buf(fd, &(node->size), sizeof(node->size));
        if (lseek(fd, node->size, SEEK_CUR) < 0) {
            perror("seeking error");
        }
        read_to_buf(fd, &(node->offset), sizeof(node->offset));
        node->structsize = node->size + sizeof(node->size) + sizeof(node->offset);
        node->totalsize += node->size;
        if (lseek(fd, node->offset - node->structsize, SEEK_CUR) < 0) {
            perror("seeking error");
        }
    }
    printf("%lld\n%lld\n", node->number, node->totalsize);
    free(node);
    if (close(fd)) {
        perror("closing file error");
    }
    return 0;
}
