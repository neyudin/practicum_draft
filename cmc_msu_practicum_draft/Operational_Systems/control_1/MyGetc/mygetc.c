#include <stdio.h>
#include <unistd.h>

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
