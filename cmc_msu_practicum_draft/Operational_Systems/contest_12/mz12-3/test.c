#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int
main(int argc, char **argv)
{
    if (argc < 2) {
        perror("not enough arguments");
        fflush(stderr);
        return 1;
    }
    FILE *first = fopen(argv[1], "r");
    FILE *second = fopen(argv[2], "r");
    int num1;
    int num2;
    if ((fscanf(first, "%d", &num1) == 1) && (fscanf(second, "%d", &num2) == 1)) {
        while (!(feof(first) || feof(second))) {
            while (num1 < num2) {
                if (fscanf(first, "%d", &num1) < 1) {
                    break;
                }
            }
            while (num2 < num1) {
                if (fscanf(second, "%d", &num2) < 1) {
                    break;
                }
            }
            while (num1 == num2) {
                printf("%d\n", num1);
                if (fscanf(first, "%d", &num1) < 1) {
                    break;
                }
                if (fscanf(second, "%d", &num2) < 1) {
                    break;
                }
            }
        }
    }
    fclose(first);
    fclose(second);
    return 0;
}