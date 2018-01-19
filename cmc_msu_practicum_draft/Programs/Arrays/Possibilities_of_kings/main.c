#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void)
{
    int desk [8] [8];
    int i, j;
    for (i = 0; i < 8; ++i)
        for (j = 0; j < 8; ++j)
            desk[i][j] = 0;
    char str[129];
    scanf("%s", str);
    int strwidth = strlen(str)-1, count;
    for (count = 0; count < strwidth; count+=2) {
        desk[str[count]-'a'][str[count+1]-'1'] = 12;
    }
    for (i = 0; i < 8; ++i)
        for (j = 0; j < 8; ++j) {
            if (desk[i][j] > 8) {
                if ((i-1 >= 0) && (j-1 >= 0)) {
                    desk[i-1][j-1] += 1;
                    desk[i-1][j] += 1;
                    desk[i][j-1] += 1;
                }
                if ((i-1 >= 0) && (j+1 <= 7)) {
                    desk[i-1][j] += 1;
                    desk[i-1][j+1] += 1;
                    desk[i][j+1] += 1;
                }
                if ((i+1 <= 7) && (j-1 >= 0)) {
                    desk[i][j-1] += 1;
                    desk[i+1][j-1] += 1;
                    desk[i+1][j] += 1;
                }
                if ((i+1 <= 7) && (j+1 <= 7)) {
                    desk[i][j+1] += 1;
                    desk[i+1][j+1] += 1;
                    desk[i+1][j] += 1;
                }
            }
    }
    count = 0;
    for (i = 0; i < 8; ++i)
        for (j = 0; j < 8; ++j) {
            if (desk[i][j]==0)
                ++count;
        }
    printf("%d\n",count);
    return 0;
}
