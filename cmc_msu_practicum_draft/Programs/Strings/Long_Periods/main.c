#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void perios_array (int p_a[], int z_a[], int len_p_a) {
    int i;
    p_a[len_p_a - 1] = len_p_a - 1;
    for (i = 0; i < len_p_a - 1; ++i) {
        if (len_p_a - i - 1 == z_a[i]) {
            p_a[i] = i;
        }
    }
    for (i = 0; i < len_p_a - 1; ++i) {
        if (p_a[i]) {
            printf("%d\t", p_a[i]);
        }
	}
	printf("%d", p_a[len_p_a - 1]);
}

int main(void)
{
    char s[1000002];
    fgets (s, 1000002, stdin);
    s[strlen( s) - 1] = '\0';
    int i, left_end, right_end, len_s = strlen(s);
	int z_function[len_s], periods[len_s + 1];
	for (i = 0; i < len_s; ++i) {
        z_function[i] = 0;
        periods[i] = 0;
	}
	left_end = 0;
	right_end = 0;
	for (i = 1; i < len_s; ++i) {
        int z_val;
		if (i <= right_end) {
		    if (right_end - i + 1 > z_function[i - left_end]) {
                z_val = z_function[i - left_end];
		    } else {
                z_val = right_end - i + 1;
		    }
            z_function[i] = z_val;
		}
		while ((s[z_function[i]] == s[i + z_function[i]]) && (i + z_function[i] < len_s)) {
            ++z_function[i];
		}
		if (i + z_function[i] - 1 > right_end){
            left_end = i;
            right_end = i + z_function[i] - 1;
		}
	}
	++len_s;
	perios_array(periods, z_function, len_s);
    return 0;
}
