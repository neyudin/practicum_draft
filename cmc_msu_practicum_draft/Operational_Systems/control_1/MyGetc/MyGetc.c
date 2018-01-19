#include <stdio.h>
#include <unistd.h>

struct MyFile
{
    int fd; // файловый дескриптор для чтения
    int size; // размер буфера (> 0)
    char *buf; // буфер (non-NULL)

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
