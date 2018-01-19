#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void format (char x[],int len_x) {/** ? == NAN */
    int i, count = 0;
    for (i = 0; i < len_x; ++i) {
        if (((x[i] < '/') || (x[i] > '9')) && (x[i] != '+') && (x[i] != '-') && (x[i] != '*')) {/**if not (number or operation)*/
            x[i] = '#';
        }
    }
    for (i = 0; i < len_x - 1; ++i) {/** ? ? */
        if (((x[i + 1] < '0') || (x[i + 1] > '9')) && ((x[i] < '0') || (x[i] > '9'))) {
            x[i] = '#';
            x[i + 1] = '#';
        }
    }
    if ((x[0] < '0') || (x[0] > '9')) {
        x[0] = '#';
    }
    if ((x[len_x - 1] < '0') || (x[len_x - 1] > '9')) {
        x[len_x - 1] = '#';
    }
    for (i = 0; i < len_x - 1; ++i) {/**lonely numbers not for us*/
        if ((x[i] == '#') && (x[i + 1] > 47) && (x[i + 1] < 58)) {
            ++i;
            while ((x[i] > 47) && (x[i] < 58)) {
                ++i;
                ++count;
            }
            if (x[i] == '#') {
                i -= count;
                while (count) {
                    x[i] = '#';
                    ++i;
                    --count;
                }
            } else {
                count = 0;
            }
        }
    }
    /**/
}

int main(void)
{
    char a[2002];
    scanf("%s", a);
    a[strlen(a)] = '\0';
    int len_a = strlen(a), i, e_1 = 0, e_2 = 0, res, mark = 0;
    if (len_a) {
    format(a, len_a);
    for (i = 0; i < len_a + 1; ++i) {
        if ((a[i] > '/') && (a[i] < ':')) {
            e_1 *= 10;
            e_1 += ((int) a[i]) - ((int) '0');
        } else {
            if (mark) {
                switch (mark) {
                    case 1: {
                        res = e_2 + e_1;
                        if (abs(res) <= 120000) {
                            printf("%d + %d = %d\n", e_2, e_1, res);
                        }
                        mark = 0;
                        break;
                    }
                    case 2: {
                        res = e_2 - e_1;
                        if (abs(res) <= 120000) {
                            printf("%d - %d = %d\n", e_2, e_1, res);
                        }
                        mark = 0;
                        break;
                    }
                    case 3: {
                        res = e_2 * e_1;
                        if (abs(res) <= 120000) {
                            printf("%d * %d = %d\n", e_2, e_1, res);
                        }
                        mark = 0;
                        break;
                    }
                    case 4: {
                        if (e_1) {
                            res = e_2 / e_1;
                            if (abs(res) <= 120000) {
                                printf("%d / %d = %d\n", e_2, e_1, res);
                            }
                        }
                        mark = 0;
                        break;
                    }
                    default: {
                        break;
                    }
                }
            }
            switch (a[i]) {
                case '+': {
                    mark = 1;
                    break;
                }
                case '-': {
                    mark = 2;
                    break;
                }
                case '*': {
                    mark = 3;
                    break;
                }
                case '/': {
                    mark = 4;
                    break;
                }
                default: {
                    break;
                }
            }
            e_2 = e_1;
            e_1 = 0;
        }
    }}/*
    printf("%s", a);*/
    return 0;
}
