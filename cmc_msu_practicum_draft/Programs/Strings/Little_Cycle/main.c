#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char s[2000001], k[2000001];
    scanf("%s", s);
    s[strlen(s)] = '\0';
    int len_s = strlen(s), i;
    for (i = 0; i <= len_s; ++i) {
        k[i] = s[i];
    }
    strcat(s, k);
    int len2s = strlen(s);
    int poi_beg_shift, m;
    for (i = 0, poi_beg_shift = 0; i < len_s; m = 0) {
        poi_beg_shift = i;
        int poi_beg_unsorted = i + 1;
        int poi_current = i;
        for (m = 0; (poi_beg_unsorted < len2s) && (s[poi_current] <= s[poi_beg_unsorted]); ++poi_beg_unsorted) {
            if (s[poi_beg_unsorted] > s[poi_current]) {
                poi_current = i;
            } else {
                poi_current += 1;
            }
        }
        for (m = 0; i <= poi_current; i += (poi_beg_unsorted - poi_current)) {}
    }
    for (m = poi_beg_shift; m < len_s; ++m) {
        printf("%c", s[m]);
    }
    for (m = 0; m < poi_beg_shift; ++m) {
        printf("%c", s[m]);
    }
    return 0;
}
