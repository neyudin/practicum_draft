#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(int argc, char **argv)
{
    if (argc != 2) {
        perror("not enough arguments");
        return 2;
    }
    int pipefd[2][2] = {{0}};
    if (pipe(pipefd[0]) == -1 || pipe(pipefd[1]) == -1) {
        perror("pipe");
        return 4;
    }
    int childpid[2] = {0};
    int buf = 0;
    int check = strtol(argv[1], NULL, 10);
    childpid[0] = fork();
    if (childpid[0]) {
        childpid[1] = fork();
    } else {
        close(pipefd[0][1]);
        close(pipefd[1][0]);
        FILE *readpipe = fdopen(pipefd[0][0], "r");
        FILE *inpipe = fdopen(pipefd[1][1], "w");
        while (fscanf(readpipe, "%d", &buf)) {
            if (buf > 0 && buf < check) {
                printf("1 %d\n", buf);
                fflush(stdout);
            } else {
                break;
            }
            fprintf(inpipe, "%d ", ++buf);
            fflush(inpipe);
        }
        fclose(readpipe);
        fclose(inpipe);
        close(pipefd[0][0]);
        close(pipefd[1][1]);
        return 0;
    }
    if (childpid[1]) {
        close(pipefd[1][0]);
        close(pipefd[1][1]);
        close(pipefd[0][0]);
        FILE *inpipe = fdopen(pipefd[0][1], "w");
        fprintf(inpipe, "%d ", ++buf);
        fflush(inpipe);
        fclose(inpipe);
        close(pipefd[0][1]);
        wait(NULL);
        wait(NULL);
        printf("Done\n");
        fflush(stdout);
    } else {
        close(pipefd[0][0]);
        close(pipefd[1][1]);
        FILE *readpipe = fdopen(pipefd[1][0], "r");
        FILE *inpipe = fdopen(pipefd[0][1], "w");
        while (fscanf(readpipe, "%d", &buf)) {
            if (buf > 0 && buf < check) {
                printf("2 %d\n", buf);
                fflush(stdout);
            } else {
                break;
            }
            fprintf(inpipe, "%d ", ++buf);
            fflush(inpipe);
        }
        fclose(inpipe);
        fclose(readpipe);
        close(pipefd[0][1]);
        close(pipefd[1][0]);
    }
    return 0;
}