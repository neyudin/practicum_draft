#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(char *string1, char *string2) {
    int i;
    for (i = 0; (*string1 == *string2) && (*string1 != '\0') && (*string2 != '\0'); ++string1, ++string2, ++i) {}
    if (*string1 == '\0') {
        if (*string2 == '\0') {
            return 0;
        } else {
            return -1;
        }
    } else {
        if (*string2 == '\0') {
            return 1;
        } else {
            if ((*string1 < 96 && *string2 < 96) || (*string1 > 96 && *string2 > 96)) {
                if (*string1 - *string2 > 0) {
                    return 1;
                } else {
                    if (*string1 == *string2) {
                        return 0;
                    } else {
                        return -1;
                    }
                }
            }
            if (*string1 < 96 && *string2 > 96) {
                return 1;
            } else {
                return -1;
            }
        }
    }

    return 0;
}

static void QuickSort (char **L, int left, int right) {
    int i, j;
        i = left; j = right;
        char *comp, *tmp;
        comp = L[(left + right)/2];
        do {
            while ((compare(comp, L[i]) == 1) && i < right) {
                i++;
            }
            while ((compare(L[j], comp) == 1) && j > left) {
                j--;
            }
            if (i <= j) {
                tmp = L[i];
                L[i] = L[j];
                L[j] = tmp;
                i++;
                j--;
            }
        } while (i <= j);
        if (left < j)
            QuickSort (L, left, j);
        if (i < right)
            QuickSort (L, i, right);
}

int main(void)
{
    int N, i;
    scanf("%d\n", &N);
    char **L, *c = malloc(9000001);
    L = (char **) malloc(9000000 + N);
    int length[N];
    for (i = 0; i < N; ++i) {
        scanf("%s", c);
        length[i] = strlen(c);
        L[i] = malloc(length[i] + 1);
        strcpy(L[i], c);
    }
    QuickSort(L, 0, (N - 1));
    for (i = 0; i < N; ++i) {
        printf("%s\n", L[i]);
    }
    return 0;
}
