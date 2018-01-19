#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int
main(int argc, char *argv[])
{
    if (argc < 3) {
        perror("not enough arguments");
        return 1;
    }
    int c;
    struct MyFile *node = calloc(1, sizeof(*node));
    node->fd = open(argv[1], O_RDONLY);
    node->size = strtol(argv[2], NULL, 10);
    node->buf = calloc(1, node->size);
    for (unsigned long long i = 0; (c = mygetc(node)) != EOF; ++i) {
        printf("%llu got <%c>\n", i, c);
        if (node->used == node->size) {
            printf("----------buffer is full\n");
        }
    }
    free(node->buf);
    if (close(node->fd)) {
        perror("closing error");
        return 2;
    }
    free(node);
    return 0;
}
