#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

enum
{
    GID_COUNT = 32,
    STR_LEN = 1022,
    BASE = 10
};

struct process
{
    unsigned uid;
    unsigned gid[GID_COUNT];
    unsigned gid_count;
    unsigned op;
};

struct file
{
    unsigned fuid;
    unsigned fgid;
    unsigned fperms;
    char *name;
};

void
get_user_info(struct process *unit)
{
    unsigned i, str_len;
    char gids[STR_LEN], *pend;
    if (scanf("%u\n", &(unit->uid)) <= 0) {
        perror("reading error");
        return;
    }
    pend = fgets(gids, sizeof(gids), stdin);
    str_len = strlen(pend);
    while (str_len > 0 && isspace(pend[str_len - 1])) --str_len;
    pend[str_len] = '\0';
    for (i = 0; i < GID_COUNT && *pend != '\0'; ++i) {
        unit->gid[i] = strtol(pend, &pend, BASE);
    }
    unit->gid_count = i;
    if (scanf("%o\n", &(unit->op)) <= 0) {
        perror("reading error");
        return;
    }
}

char *
format_string(char *format, struct file *unit)
{
    unsigned str_len = strlen(format), count;
    while (str_len > 0 && isspace(format[str_len - 1])) --str_len;
    format[str_len] = '\0';
    if (sscanf(format, "%u%o%n", &(unit->fgid), &(unit->fperms), &count) <= 0) {
        perror("reading error");
        return NULL;
    }
    while(count < str_len && isspace(format[count])) ++count;
    return format + count;
}

int
check_gid(struct process *user, struct file *unit)
{
    for (unsigned i = 0; i < user->gid_count; ++i) {
        if (user->gid[i] == unit->fgid) {
            return 1;
        }
    }
    return 0;
}

int
check_gperms(unsigned op, unsigned gperms)
{
    return !(op & ~gperms);
}

int
check_perms(struct process *user, struct file *unit)
{
    if (user->uid == unit->fuid) {
        return check_gperms(user->op, (unit->fperms & (7 << 6)) >> 6);
    }
    if (check_gid(user, unit)) {
        return check_gperms(user->op, (unit->fperms & (7 << 3)) >> 3);
    }
    return check_gperms(user->op, unit->fperms & 7);
}

int
main(void)
{
    struct process *user = calloc(1, sizeof(*user));
    struct file *object = calloc(1, sizeof(*object));
    char format[STR_LEN] = {0};
    get_user_info(user);
    while (scanf("%u", &(object->fuid)) && fgets(format, sizeof(format), stdin)) {
        object->name = format_string(format, object);
        if (check_perms(user, object)) {
            printf("%s\n", object->name);
        }
    }
    free(object);
    free(user);
    return 0;
}
