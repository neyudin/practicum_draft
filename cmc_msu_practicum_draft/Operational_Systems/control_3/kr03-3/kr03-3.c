#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

enum
{
    BASE = 10
};

typedef struct gens
{
    int N;
    int G1;
    int G2;
    int pipefd[2];
    char *filename;
} gens;

void
generation(int cur, gens *node)
{
    if (cur == node->G1) {
        if ((cur != node->N) && !fork()) {
            generation(++cur, node);
            return;
        }
        close(node->pipefd[0]);
        FILE *pipe_write = fdopen(node->pipefd[1], "w");
        FILE *file = fopen(node->filename, "r");
        int c = 'a';
        while (c != EOF) {
            c = fgetc(file);
            if (c == EOF) {
                break;
            }
            fprintf(pipe_write, "%c", c);
            fflush(pipe_write);
        }
        fclose(file);
        fclose(pipe_write);
        close(node->pipefd[1]);
        wait(NULL);
        return;
    }
    if (cur == node->G2) {
        if ((cur != node->N) && !fork()) {
            generation(++cur, node);
            return;
        }
        close(node->pipefd[1]);
        FILE *pipe_read = fdopen(node->pipefd[0], "r");
        int c = 'a';
        while (c != EOF) {
            c = fgetc(pipe_read);
            if (c == EOF) {
                break;
            }
            printf("%c", c);
            fflush(stdout);
        }
        fclose(pipe_read);
        close(node->pipefd[0]);
        wait(NULL);
        return;
    }
    if ((cur != node->N) && !fork()) {
        generation(++cur, node);
    } else {
        close(node->pipefd[0]);
        close(node->pipefd[1]);
        wait(NULL);
    }
}

int
main(int argc, char **argv)
{
    gens node;
    node.N = strtol(argv[1], NULL, BASE);
    node.G1 = strtol(argv[2], NULL, BASE);
    node.G2 = strtol(argv[3], NULL, BASE);
    node.filename = argv[4];
    if (pipe(node.pipefd) == -1) {
        perror("pipe()");
        fflush(stderr);
        return 0;
    }
    if (!fork()) {
        generation(1, &node);
        return 0;
    }
    close(node.pipefd[0]);
    close(node.pipefd[1]);
    wait(NULL);
    return 0;
}