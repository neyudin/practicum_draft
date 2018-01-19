#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct line {
    char op, type;
    unsigned addr;
    unsigned size;
    int unit;
};

struct unittime {
    unsigned r_time;
    unsigned w_time;
    unsigned wr_time;
    unsigned long long timer;
};

void
copy(struct line *arg_1, struct line *arg_2)
{
    arg_1->op = arg_2->op;
    arg_1->type = arg_2->type;
    arg_1->addr = arg_2->addr;
    arg_1->size = arg_2->size;
    arg_1->unit = arg_2->unit;
}

int
main(int argc, char **argv)
{
    struct unittime timer;
    timer.r_time = strtol(argv[1], NULL, 10);
    timer.w_time = strtol(argv[2], NULL, 10);
    timer.wr_time = strtol(argv[3], NULL, 10);
    timer.timer = 0;
    struct line prev;
    memset(&prev, 0, sizeof(prev));
    struct line cur;
    memset(&cur, 0, sizeof(cur));
    int flag = 0;
    while (scanf("%c%c %x %u %d\n", &cur.op, &cur.type, &cur.addr, &cur.size, &cur.unit) > 4) {
        if (flag && prev.op == 'W' && cur.op == 'R' && prev.addr == cur.addr && prev.size == cur.size) {
            timer.timer -= timer.w_time;
            timer.timer += timer.wr_time;
            copy(&prev, &cur);
            continue;
        } else {
            flag = 1;
        }
        if (cur.op == 'R') {
            timer.timer += timer.r_time;
        } else {
            timer.timer += timer.w_time;
        }
        copy(&prev, &cur);
    }
    printf("%llu\n", timer.timer);
    return 0;
}
