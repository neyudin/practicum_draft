#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    long long **matrix, trace = 0, range, i, j, k, tmp[8];
    FILE *input = fopen("matrix.in", "rb");
    range = fgetc(input);
    range <<= 8;
    range |= fgetc(input);
    matrix = (long long **) calloc(range * range, sizeof(long long));
    for (i = 0; i < range; ++i) {
        matrix[i] = (long long *) calloc(range, sizeof(long long));
        for (j = 0; j < range; ++j) {
            k = 0;
            while (k < 4) {
                matrix[i][j] |= fgetc(input);
                if (k != 3) {
                    matrix[i][j] <<= 8;
                }
                ++k;
            }
            if (i == j) {
                if (matrix[i][j] & 0x80000000) {
                    matrix[i][j] |= 0xffffffff00000000;
                }
                trace += matrix[i][j];
            }
        }
    }
    fclose(input);
    for (i = 0; i < 8; ++i)
        tmp[i] = (trace >> (8 * i)) & 0xff;
    FILE *output = fopen("trace.out", "wb");
    for (i = 0; i < 8; ++i)
        fprintf(output, "%c", (char) tmp[7 - i]);
    fclose(output);
    return 0;
}
