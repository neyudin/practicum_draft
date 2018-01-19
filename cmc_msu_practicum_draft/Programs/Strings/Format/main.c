#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int increase (char x_i,int limit,int i,int j,int len_x,int num) {
    int r, l_mid;
    switch (x_i) {
                case ' ': {
                    ++j;
                    if(j < ((limit - len_x) % num) + 1) {
                        l_mid = (limit - len_x) / num + 1;
                    } else {
                        l_mid = (limit - len_x) / num ;
                    }
                    for (r = i; r < i + l_mid + 1; ++r) {
                        printf(" ");
                    }
                    break;
                }
                default: {
                    printf("%c", x_i);
                }
            }
    return j;
}

int main(void)
{
    char s[1000002];
    int j = 0, i, k;
    scanf("%d\n", &k);
    fgets (s, 1000002, stdin);
    s[strlen( s) - 1] = '\0';
    int len_s = strlen(s), n = 0;
    if (len_s != k) {
        for (i = 0; i < len_s; ++i) {
            if (s[i] == ' ') {
                ++n;
            }
        }
        for (i = 0; i < len_s; ++i) {
            j = increase(s[i], k, i, j, len_s, n);
        }
    } else {
        printf("%s", s);
    }
    return 0;
}
