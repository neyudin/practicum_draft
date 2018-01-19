#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

struct node
{
    int key;
    int left_idx;
    int right_idx;
};

void
reader(int fd, struct node *unit)
{
    for (ssize_t dif = sizeof(*unit), count = 0, already_read = 0; dif > 0; dif -= count) {
        count = read(fd, ((char *) unit) + already_read, dif);
        if (count < 0) {
            perror("reading error");
            return;
        }
        already_read += count;
    }
}

void
read_tree(int fd, struct node *unit)
{
    reader(fd, unit);
    int num = unit->key;
    int left = unit->left_idx;
    int right = unit->right_idx;
    if (right) {
        if(lseek(fd, sizeof(*unit) * right, SEEK_SET) < 0) {
            perror("seeking error");
            return;
        }
        read_tree(fd, unit);
    }
    printf("%d\n", num);
    if (left) {
        if(lseek(fd, sizeof(*unit) * left, SEEK_SET) < 0) {
            perror("seeking error");
            return;
        }
        read_tree(fd, unit);
    }
}

int
main(int argc, char *argv[])
{
    if (argc < 2) {
        perror("not enough arguments");
        return 0;
    }
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("file descriptor error");
        return 0;
    }
    struct node *unit = calloc(1, sizeof(*unit));
    if (unit == NULL) {
        perror("null pointer error");
        return 0;
    }
    read_tree(fd, unit);
    free(unit);
    close(fd);
    return 0;
}
