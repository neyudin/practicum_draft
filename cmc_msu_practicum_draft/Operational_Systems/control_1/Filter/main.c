#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

enum
{
	ARGC = 4,
	BASE = 10
};

int
check_suffix(const char *name, const char *suffix)
{
    int len_n = strlen(name), len_s = strlen(suffix);
    if (len_n < len_s) {
        return 0;
    }
    return !strncmp(name + len_n - len_s, suffix, len_s);
}

int
check_str(const char *new_str, const char *previous)
{
    if (strncmp(new_str, previous, PATH_MAX) < 0) {
        return 1;
    }
    return 0;
}

int
main(int argc, char *argv[])
{
    if (argc < ARGC) {
        perror("not enough arguments");
        return 1;
    }
    DIR *directory = opendir(argv[1]);
    unsigned long long max_file_size = 0;
    unsigned long long total_size = 0;
    char filename[PATH_MAX] = {0};
    char path[PATH_MAX] = {0};
    struct dirent *node;
    struct stat buf;
    while ((node = readdir(directory)) != NULL) {
        if (!snprintf(path, sizeof(path), "%s/%s", argv[1], node->d_name)) {
            perror("snprintf error");
            return ARGC - 1;
        }
        if (lstat(path, &buf)) {
            continue;
        }
        if (S_ISREG(buf.st_mode)) {
            total_size += buf.st_size;
            if (check_suffix(node->d_name, argv[ARGC - 1])) {
                if (buf.st_size > max_file_size) {
                    strncpy(filename, node->d_name, sizeof(filename));
                    max_file_size = buf.st_size;
                } else if (buf.st_size == max_file_size && check_str(node->d_name, filename)){
                    strncpy(filename, node->d_name, sizeof(filename));
                }
            }
        }
    }
    if (total_size > strtoll(argv[2], NULL, BASE)) {
        printf("%s\n", filename);
    }
    if (closedir(directory)) {
        perror("closing directory error");
        return 2;
    }
    return 0;
}
