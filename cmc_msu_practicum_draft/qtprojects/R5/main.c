#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 4096

int f(char *buffer, char *a_string, char *b_string) {
    int i;
    for (i = 0; i < 256; ++i) {
        buffer[i] = (unsigned char) i;
    }
    i = 0;
    if (strlen(a_string) == strlen(b_string))
        ++i;
    if (i) {
        for (i = 0; a_string[i] != '\0'; ++i)
            buffer[(int) ((unsigned char) a_string[i])] = b_string[i];
        return 1;
    }
    return 0;
}

char *p(char *buffer, char *string) {
    int i;
    for (i = 0; string[i] != '\0'; ++i) //or '\n'
        string[i] = buffer[(int) ((unsigned char) string[i])];
    return string;
}

char *s(char *string, int buffer_size) {
    --buffer_size;
    string = fgets(string, buffer_size, stdin);
    //scanf("%s", string);
    string[buffer_size] = '\0';
    return string;
}

int main(void)
{
    char *src = malloc(256), *dst = malloc(256), *buf = malloc(256), *c = malloc(BUF_SIZE);
    int i = 0;
    src = s(src, 256);
    dst = s(dst, 256);
    if (f(buf, src, dst))
        for (scanf("%d", &i), s(c, BUF_SIZE); i > 0; --i)
            printf("%s", p(buf, s(c, BUF_SIZE)));
    free(src);
    free(dst);
    free(buf);
    free(c);
    return 0;
}
