#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>

int
main(int argc, char *argv[])
{
    if (argc < 2) {
        perror("not enough arguments");
        return 1;
    }
    DIR *file = opendir(argv[1]);   
    struct dirent *node;
    char path[PATH_MAX] = {0};
    struct stat buf;
    unsigned long long total_size = 0;
    while ((node = readdir(file)) != NULL) {
        if (!snprintf(path, sizeof(path), "%s/%s", argv[1], node->d_name)) {
            perror("snprintf error");
            return 3;
        }
        if (lstat(path, &buf)) {
            continue;
        }
        if (S_ISREG(buf.st_mode)) {
            total_size += buf.st_size;
        }
    }
    printf("%llu\n", total_size);
    if (closedir(file)) {
        perror("closing directory error");
        return 2;
    }
    return 0;
}
