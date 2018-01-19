#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(void)
{
    char *a = (char *) calloc(10002, sizeof(char)), *b = (char *) calloc(10002, sizeof(char)), c = '5', action = '+';
    int i, j, k, index, *res = (int *) calloc(20002, sizeof(int));
    i = 0;
    while (c) {
        scanf("%c", &c);
        if (c < 48) {
            action = c;
            break;
        }
        a[i] = c;
        ++i;
    }
    k = i;
    a[i] = '\0';
    j = 0;
    while (c > 32) {
        scanf("%c", &c);
        b[j] = c;
        ++j;
    }
    --j;
    b[j] = '\0';
    int len_a = i, len_b = j;
    for (i = 0, c = '0'; i < len_a/2; ++i) {
        c = a[i];
        a[i] = a[len_a - i - 1];
        a[len_a - i - 1] = c;
    }
    for (i = 0, c = '0'; i < len_b/2; ++i) {
        c = b[i];
        b[i] = b[len_b - i - 1];
        b[len_b - i - 1] = c;
    }
    if (action == '+') {/**/
        int sum;
        for (i = 0, res[0] = 0; (i < len_a) || (i < len_b); ++i) {
            if (i < len_b) {
                sum = b[i] - '0';
            } else {
                sum = 0;
            }
            if (i < len_a) {
                res[i] += a[i] + sum - '0';
            } else {
                res[i] += sum;
            }
            if (res[i] > 9) {
                res[i + 1] = res[i]/10;
                res[i] %= 10;
            } else {
                res[i + 1] = 0;
            }
        }
        for (; res[i] == 0; --i) {}
        for (k = i; k + 1 > 0; --k) {
            printf("%d", res[k]);
        }
        if (i + 1 == 0) {
            printf("0");
        }
    }
    if (action == '-') {/**/
        char *tmp;
        int t = 1, take;
        if (len_a < len_b) {
            printf("-");
            tmp = a;
            a = b;
            b = tmp;
            t = len_a;
            len_a = len_b;
            len_b = t;
        }
        if (len_a == len_b) {
            for (i = len_a - 1; i + 1 > 0; --i) {
                if (a[i] != b[i]) {
                    break;
                }
            }
            if (i == -1) {
                printf("0");
                return 0;
            }
            if (b[i] > a[i]) {
                printf("-");
                tmp = a;
                a = b;
                b = tmp;
            }
        }
        for (i = 0, take = 0; i < len_b; ++i) {
            res[i] = a[i] - b[i] - take;
            if (res[i] < 0) {
                take = 1;
                res[i] += 10;
            } else {
                take = 0;
            }
        }
        for (i = len_b; i < len_a; ++i) {
            res[i] = a[i] - '0' - take;
            if (res[i] < 0) {
                res[i] += 10;
                take = 1;
            } else {
                take = 0;
            }
        }
        for (k = i - 1; res[k] == 0; --k);
        for (i = k; i + 1 > 0; --i) {
            printf("%d", res[i]);
        }
    }
    if (action == '*') {/**/
        char *tmp;
        int i_i, i_j, height, t;
        if (len_a > len_b) {
            index = 2 * len_a;
            height = len_b;
        } else {
            index = 2 * len_b;
            height = len_a;
            tmp = a;
            a = b;
            b = tmp;
            t = len_a;
            len_a = len_b;
            len_b = t;
        }
        int step = 0;
        for (i_i = 0; i_i < height; ++i_i) {
            for (i_j = step, j = 0; (i_j < index) && (j < len_a); ++i_j, ++j) {
                res[i_j] += (a[j] - '0') * (b[i_i] - '0');
            }
            ++step;
        }
        for (i_j = 0; i_j < index - 1; ++i_j) {
            res[i_j + 1] += res[i_j]/10;
            res[i_j] %= 10;
        }
        for (k = index - 1; res[k] == 0; --k);
        if (!(k + 1)) {
            printf("0");
            return 0;
        }
        for (i = k; i + 1 > 0; --i) {
            printf("%d", res[i]);
        }
    }
    return 0;
}

