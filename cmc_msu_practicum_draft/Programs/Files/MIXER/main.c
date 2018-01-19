#include <stdio.h>
#include <stdlib.h>

struct node {
    int x;
    struct node *prev, *next;
} node = { .x = 0, .prev = NULL, .next = NULL};

struct node **initializer_list (struct node **array, int N) {
    int i;
    for (i = 0; i < N; ++i) {
        array[i]->x = i + 1;
        array[i]->prev = NULL;
        array[i]->next = NULL;
    }
    array[0]->next = array[1];
    for (i = 1; i + 1 < N; ++i) {
        array[i]->next = array[i + 1];
        array[i]->prev = array[i - 1];
    }
    array[N - 1]->prev = array[N - 2];
    return array;
}

struct node *mixer (struct node **array, int N, int M, int **mix) {
    struct node *root = (struct node *) malloc(sizeof(struct node));
    if (N > 1) {
        int i = 0;
        if (array[mix[i][0]]->prev != NULL) {
            array[mix[i][0]]->prev->next = array[mix[i][1]]->next;
            if (array[mix[i][1]]->next != NULL) {
                array[mix[i][1]]->next->prev = array[mix[i][0]]->prev;
            }
            array[mix[i][0]]->prev = NULL;
            array[mix[i][1]]->next = array[0];
            array[0]->prev = array[mix[i][1]];
        }
        root = array[mix[i][0]];
        for (i = 1; i < M; ++i) {
            if (array[mix[i][0]]->prev != NULL) {
                array[mix[i][0]]->prev->next = array[mix[i][1]]->next;
                if (array[mix[i][1]]->next != NULL) {
                    array[mix[i][1]]->next->prev = array[mix[i][0]]->prev;
                }
                array[mix[i][0]]->prev = NULL;
                array[mix[i][1]]->next = array[mix[i - 1][0]];
                array[mix[i - 1][0]]->prev = array[mix[i][1]];
            }
            root = array[mix[i][0]];
        }
        return root;
    } else {
        return array[0];
    }
}

int main(void)
{
    int N, M;

    FILE *input = fopen("input.txt", "r");
    fscanf(input, "%d%d", &N, &M);
    int **mix = (int **) malloc(M * 2 * sizeof(int)), i;
    for (i = 0; i < M; ++i) {
        mix[i] = (int *) malloc(2 * sizeof(int));
        fscanf(input, "%d%d", &mix[i][0], &mix[i][1]);
        --mix[i][0]; --mix[i][1];
    }
    fclose(input);

    int y;
    struct node **array = (struct node **) malloc(N * sizeof(struct node *));
    for (y = 0; y < N; ++y) {
        array[y] = (struct node *) malloc(sizeof(struct node));
    }
    array = initializer_list(array, N);struct node *root = (struct node *) malloc(sizeof(struct node));root = array[0];
    root = mixer(array, N, M, mix);/**spinning**/

    FILE *output = fopen("output.txt", "w+");
    if (N > 1) {
        for (i = 0; root != NULL; ++i, root = root->next) {
            fprintf(output,"%d", root->x);
            if (i != N - 1) {
                fprintf(output, " ");
            }
        }
    } else {
        fprintf(output,"%d", root->x);
    }
    fclose(output);

    free(mix);
    free(array);
    free(root);

    return 0;
}
