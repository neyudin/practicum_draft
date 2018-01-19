#include <stdio.h>
#include <stdlib.h>

int gcd (int a, int b) {
	while (b) {
		a %= b;
		int p = a;
        a = b;
        b = p;
	}
	return a;
}

int *gcd_line (int *line_1, int length) {
    int answer = line_1[0], index = 0;
    index = 1;
    while (index < length + 1) {
                    answer = gcd(answer, line_1[index]);
        ++index;
    }
    for (index = 0; index < length + 1; ++index) {
        line_1[index] /= answer;
    }
    return line_1;
}

/*int *division (int *line_1, int length, int temp_div) {
    int i;
    for (i = 0; i < length + 1; ++i) {
        line_1[i] /= temp_div;
    }
    return line_1;
}*/

int **Gauss_Jordan_elimination(int **matrix, int N) {
    int j, temp_div, step, id, index;
    for (index = 0; index < N; ++index) {
        matrix[index] = gcd_line(matrix[index], N);
    }
    printf("timing:\n");
     for (j = 0; j < N; ++j) {
        for (id = 0; id < N + 1; ++id) {
            printf("%d\t", matrix[j][id]);
        }
        printf("\n");
    }
    for (step = 0; step < N; ++step) {
        for (j = 0; j < N; ++j) {
            if (j != step) {
                temp_div = gcd(matrix[j][step], matrix[step][step]);
                for (id = step; id < N + 1; ++id) {
                    matrix[j][id] =  (-1) * (matrix[step][id]/temp_div) * matrix[j][step] + (matrix[j][id]/temp_div) * matrix[step][step];
                }
            }
        }
    }
    return matrix;
}

int *Substitution(int **matrix, int N) {
    int j, *result = (int *) calloc(N, sizeof(int));
    for (j = N - 1; j + 1 > 0; --j) {
        result[j] = matrix[j][N] / matrix[j][j];
    }
    return result;
}

int main(void)
{
    int N;
    scanf("%d", &N);
    int **matrix = (int **) calloc(N * (N + 1), sizeof(int)), i, j, *result = (int *) calloc(N, sizeof(int));
    for (i = 0; i < N; ++i) {
        matrix[i] = (int *) calloc(N + 1, sizeof(int));
        for (j = 0; j < N + 1; ++j) {
            scanf("%d", &matrix[i][j]);
        }
    }
    matrix = Gauss_Jordan_elimination(matrix, N);
    printf("after_Gauss_Jordan_elimination:\n");
    for (j = 0; j < N; ++j) {
        for (i = 0; i < N + 1; ++i) {
            printf("%d\t", matrix[j][i]);
        }
        printf("\n");
    }
    result = Substitution(matrix, N);
    printf("after_substitution:\n");
    for (j = 0; j < N; ++j) {
        for (i = 0; i < N + 1; ++i) {
            printf("%d\t", matrix[j][i]);
        }
        printf("\n");
    }
    printf("result:\n");
    for (j = 0; j < N; ++j) {
        printf("%d\n", result[j]);
    }
    return 0;
}
