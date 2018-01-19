#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <strings.h>

enum
{
    A_MUL = 64
};

struct vector
{
    char **v;
    int a;
    int u;
};

struct buffer
{
    char read_dir_buf[PATH_MAX];
    struct stat buf;
    struct dirent *file;
    DIR *cat;
    DIR *check;
};

int
compare(const void *arg_1, const void *arg_2)
{
    return strcasecmp(* (char **) arg_1, * (char **) arg_2);
}

void
read_dir(const char *path, struct vector *node, struct buffer *buf)
{
    while ((buf->file = readdir(buf->cat)) != NULL) {
        if (!strncmp(buf->file->d_name, ".", 2) || !strncmp(buf->file->d_name, "..", 3)) {
            continue;
        }
        snprintf(buf->read_dir_buf, sizeof(buf->read_dir_buf), "%s/%s", path, buf->file->d_name);
        if (lstat(buf->read_dir_buf, &(buf->buf))) {
            continue;
        }
        if (S_ISDIR(buf->buf.st_mode) && ((buf->check = opendir(buf->read_dir_buf)) != NULL)) {
            if (closedir(buf->check)) {
                perror("closing error");
                return;
            }
            if (node->a == node->u) {
                if(!(node->a *= 2)) {
                    node->a = A_MUL;
                }
                node->v = realloc(node->v, node->a * sizeof(*(node->v)));
            }
            node->v[node->u++] = strdup(buf->file->d_name);
        }
    }
}

void
read_cat(const char *path, struct buffer *buf)
{
    char way[PATH_MAX];
    struct vector *node = calloc(1, sizeof(*node));
    read_dir(path, node, buf);
    if (closedir(buf->cat)) {
        perror("closing error");
        return;
    }
    qsort(node->v, node->u, sizeof(*(node->v)), compare);
    for (int i = 0; i < node->u; ++i) {
        printf("cd %s\n", node->v[i]);
        snprintf(way, sizeof(way), "%s/%s", path, node->v[i]);
        buf->cat = opendir(way);
        read_cat(way, buf);
        printf("cd ..\n");
    }
    for (int i = 0; i < node->u; ++i) {
        free(node->v[i]);
    }
    free(node->v);
    free(node);
}

int
main(int argc, char *argv[])
{
    if (argc < 2) {
        perror("not enough arguments");
        return 1;
    }
    struct buffer buf;
    buf.cat = opendir(argv[1]);
    if (buf.cat) {
        read_cat(argv[1], &buf);
    }
    return 0;
}
