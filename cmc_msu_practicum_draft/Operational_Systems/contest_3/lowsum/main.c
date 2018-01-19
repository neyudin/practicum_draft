#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

enum {BUF_SIZE = 16};

int
my_scanf(char *buf)
{
    int count = read(0, buf, BUF_SIZE);
    if (count < 0) {
        perror("reading error");
    }
    return count;
}

void
parsing (void)
{
    char buf[BUF_SIZE] = {0};
    int sign_flag = 0, bon_flag = 0;
    long long num = 0, sum = 0;
    for (int count = my_scanf(buf); count > 0; count = my_scanf(buf)) {
        for (int i = 0; i < count; ++i) {
            if (isdigit(buf[i])) {
                bon_flag = 1;
                num = 10 * num + buf[i] - '0';
                continue;
            }
            if (!bon_flag) {
                if (buf[i] == ' ') {
                    continue;
                }
                if (buf[i] == '-') {
                    ++sign_flag;
                    ++bon_flag;
                    continue;
                }
                if (buf[i] == '+') {
                    ++bon_flag;
                    continue;
                }
            }
            sum += num * (sign_flag? -1: 1);
            sign_flag = 0;
            bon_flag = 0;
            num = 0;
        }
    }
    sum += num * (sign_flag? -1: 1);
    printf("%lld\n", sum);
}

int
main(int argc, char *argv[])
{
    parsing();
    return 0;
}
