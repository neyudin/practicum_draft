#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

struct Data
{
    int x;
    long long y;
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

void
reader(int fd, struct Data *unit)
{
    read_to_buf(fd, &(unit->x), sizeof(unit->x));
    read_to_buf(fd, &(unit->y), sizeof(unit->y));
}

void
write_from_buf(int fd, void *buf, int buf_size)
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

void
printer(int fd, struct Data *unit)
{
    write_from_buf(fd, &(unit->x), sizeof(unit->x));
    write_from_buf(fd, &(unit->y), sizeof(unit->y));
}

void
modify(struct Data *node, char *num) {
    node->y += node->x * atoi(num);
}

void
reverse(int fd, char *argv)
{
    struct Data *lr_node = calloc(1, sizeof(*lr_node));
    struct Data *rl_node = calloc(1, sizeof(*rl_node));
    off_t length = lseek(fd, 0, SEEK_END)/sizeof(struct Data);
    if (!length) {
        perror("file is empty");
        return;
    }
    if (lseek(fd, 0, SEEK_SET) < 0) {
        perror("seeking error");
        return;
    }
    for (off_t i = 0; i < length/2; ++i) {
        reader(fd, lr_node);
        modify(lr_node, argv);
        if (lseek(fd, sizeof(*rl_node) * (-i - 1), SEEK_END) < 0) {
            perror("seeking error");
            return;
        }
        reader(fd, rl_node);
        modify(rl_node, argv);
        if (lseek(fd, sizeof(*lr_node) * (-1), SEEK_CUR) < 0) {
            perror("seeking error");
            return;
        }
        printer(fd, lr_node);
        if (lseek(fd, sizeof(*rl_node) * i, SEEK_SET) < 0) {
            perror("seeking error");
            return;
        }
        printer(fd, rl_node);
    }
    if (length % 2) {
        reader(fd, lr_node);
        modify(lr_node, argv);
        if (lseek(fd, sizeof(*lr_node) * (-1), SEEK_CUR) < 0) {
            perror("seeking error");
            return;
        }
        printer(fd, lr_node);
    }
    free(lr_node);
    free(rl_node);
}

int
main(int argc, char *argv[])
{
    if (argc < 3) {
        perror("not enough arguments");
        return 1;
    }
    int fd = open(argv[1], O_RDWR);
    if (fd < 0) {
        perror("file descriptor error");
        return 2;
    }
    reverse(fd, argv[2]);
    if (close(fd)) {
        perror("closing error");
        return 3;
    }
    return 0;
}
