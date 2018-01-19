#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    int M, N, virus_num, i, j, k, time = 0, pop = 0;
    scanf("%d%d%d", &N, &M, &virus_num);
    int **colony;
    colony = (int **) malloc(N * M * sizeof(int));
    for (i = 0; i < M; ++i) {
        colony[i] = (int *) malloc(N * sizeof(int));
    }
    for (i = 0; i < M; ++i) {
        for (j = 0; j < N; ++j) {
            colony[i][j] = 0;
        }
    }
    int **recon;
    recon = (int **) malloc(2 * M * N * sizeof(int));
    for (i = 0; i < M * N; ++i) {
        recon[i] = (int *) malloc(2 * sizeof(int));
    }
    for (i = 0; i < M * N; ++i) {
        recon[i][0] = 0;
        recon[i][1] = 0;
    }
    for (i = 0, j = 0, k = 0; k < virus_num; ++k) {
        scanf("%d%d", &i, &j);
        recon[k][0] = i - 1;
        recon[k][1] = j - 1;
        pop = k;
        colony[i - 1][j - 1] = 1;
    }
    int step;
    for (step = 0; step < pop + 1; ++step) {
        i = recon[step][0];
        j = recon[step][1];
        if (i > 0) {
            if (colony[i - 1][j] == 0) {
                ++pop;
                recon[pop][0] = i - 1;
                recon[pop][1] = j;
                colony[i - 1][j] = colony[i][j] + 1;
            } else {
                if (colony[i - 1][j] > colony[i][j] + 1) {
                    ++pop;
                    recon[pop][0] = i - 1;
                    recon[pop][1] = j;
                    colony[i - 1][j] = colony[i][j] + 1;
                }
            }
        }
        if (i < M - 1) {
            if (colony[i + 1][j] == 0) {
                ++pop;
                recon[pop][0] = i + 1;
                recon[pop][1] = j;
                colony[i + 1][j] = colony[i][j] + 1;
            } else {
                if (colony[i + 1][j] > colony[i][j] + 1) {
                    ++pop;
                    recon[pop][0] = i + 1;
                    recon[pop][1] = j;
                    colony[i + 1][j] = colony[i][j] + 1;
                }
            }
        }
        if (j > 0) {
            if (colony[i][j - 1] == 0) {
                ++pop;
                recon[pop][0] = i;
                recon[pop][1] = j - 1;
                colony[i][j - 1] = colony[i][j] + 1;
            } else {
                if (colony[i][j - 1] > colony[i][j] + 1) {
                    ++pop;
                    recon[pop][0] = i;
                    recon[pop][1] = j - 1;
                    colony[i][j - 1] = colony[i][j] + 1;
                }
            }
        }
        if (j < N - 1) {
            if (colony[i][j + 1] == 0) {
                ++pop;
                recon[pop][0] = i;
                recon[pop][1] = j + 1;
                colony[i][j + 1] = colony[i][j] + 1;
            } else {
                if (colony[i][j + 1] > colony[i][j] + 1) {
                    ++pop;
                    recon[pop][0] = i;
                    recon[pop][1] = j + 1;
                    colony[i][j + 1] = colony[i][j] + 1;
                }
            }
        }
    }
    for (i = 0; i < M; ++i) {
        for (j = 0; j < N; ++j) {
            if (colony[i][j] > time) {
                time = colony[i][j];
            }
        }
    }
    printf("%d", (time - 1));
    return 0;
}
