#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *file_in = NULL;
    file_in = fopen("input.txt", "r");
    int mark = 1;
    long long cur = 0, res = 0;
    char cur_c;
    while (!feof(file_in)) {
        if (fscanf(file_in, "%lld", &cur)) {
            if (mark == 1) {
                res += cur;
            }
            if (mark == 2) {
                res -= cur;
            }
        }
        while (!feof(file_in)) {
            fscanf(file_in, "%c", &cur_c);
            if (cur_c == '+') {
                mark = 1;
                break;
            }
            if (cur_c == '-') {
                mark = 2;
                break;
            }
        }
    }
    fclose(file_in);
    FILE *file_out = NULL;
    file_out = fopen("output.txt", "w");
    cur = fprintf(file_out, "%lld", res);
    fclose(file_out);
    return 0;
}
