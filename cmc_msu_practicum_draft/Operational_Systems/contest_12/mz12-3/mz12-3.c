#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int
main(int argc, char **argv)
{
    if (argc == 1) {
        return 0;
    }
    if (argc > 2) {
        int **pipes = NULL;
        if (argc > 3) {
            pipes = calloc(argc - 3, sizeof(*pipes));
        }
        for (int i = 0; i < argc - 3; ++i) {
            pipes[i] = calloc(2, sizeof(**pipes));
        }
        for (int i = 0; i < argc - 3; ++i) {
            if (pipe(pipes[i]) == -1) {
                perror("pipe()");
                fflush(stderr);
                return 1;
            }
        }
        for (int i = 0; i < argc - 2; ++i) {
            int proc_id = i;
            if (!fork()) {
                FILE *first = NULL;
                FILE *second = NULL;
                if (proc_id >= ((argc - 1) >> 1) - 1) {
                    if (proc_id << 1 >= argc - 3) {
                        first = fopen(argv[(proc_id << 1) - argc + 4], "r");
                    } else {
                        first = fdopen(pipes[proc_id << 1][0], "r");
                        close(pipes[proc_id << 1][1]);
                    }
                    second = fopen(argv[(proc_id << 1) - argc + 5], "r");
                } else {
                    first = fdopen(pipes[proc_id << 1][0], "r");
                    second = fdopen(pipes[(proc_id << 1) + 1][0], "r");
                    close(pipes[proc_id << 1][1]);
                    close(pipes[(proc_id << 1) + 1][1]);
                }
                FILE *output = NULL;
                if (proc_id) {
                    output = fdopen(pipes[proc_id - 1][1], "w");
                    close(pipes[proc_id - 1][0]);
                } else {
                    output = stdout;
                }
                for (int a = 0; a < argc - 3; ++a) {
                    if ((a != proc_id << 1) && (a != (proc_id << 1) + 1) && (a != proc_id - 1)) {
                        close(pipes[a][0]);
                        close(pipes[a][1]);
                    }
                }
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
                        fprintf(output, "%d\n", num1);
                        fflush(output);
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
            fclose(output);
            if (proc_id << 1 < argc - 3) {
                close(pipes[proc_id << 1][0]);
            }
            if (proc_id < ((argc - 1) >> 1) - 1) {
                close(pipes[proc_id << 1][0]);
                close(pipes[(proc_id << 1) + 1][0]);
            }
            if (proc_id) {
                close(pipes[proc_id - 1][1]);
            }
            exit(0);
            }
        }
        for (int i = 0; i < argc - 3; ++i) {
            close(pipes[i][0]);
            close(pipes[i][1]);
        }
        for (int i = 0; i < argc - 2; ++i) {
            wait(NULL);
        }
        for (int i = 0; i < argc - 3; ++i) {
            free(pipes[i]);
        }
        if (argc > 3) {
            free(pipes);
        }
    } else {
        FILE *first = fopen(argv[1], "r");
        int num1;
        while (fscanf(first, "%d", &num1) == 1) {
            printf("%d\n", num1);
            fflush(stdout);
        }
        fclose(first);
    }
    return 0;
}