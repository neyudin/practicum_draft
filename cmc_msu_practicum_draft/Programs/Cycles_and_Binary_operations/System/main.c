#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    long long a11, a12, b1, x, y, a21, a22, b2, i11, i12, i21, i22, j1, j2, b, c;
    scanf("%lld%lld\n", &a11, &a12);
    scanf("%lld%lld\n", &a21, &a22);
    scanf("%lld%lld", &b1, &b2);
    long long s = 31;
    x = 0;
    y = 0;
    int quit;
    for (s = s; s >= 0; --s) {
        i11 = (a11 & (1 << s)) >> s;
        i12 = (a12 & (1 << s)) >> s;
        i21 = (a21 & (1 << s)) >> s;
        i22 = (a22 & (1 << s)) >> s;
        j1 = (b1 & (1 << s)) >> s;
        j2 = (b2 & (1 << s)) >> s;
        quit = 0;
        for (b = 0; b <= 1; ++b) {
            for (c = 0; c <= 1; ++c) {
                if ( ( ((i11&b)^(i12&c)) == j1 ) && ( ((i21&b)^(i22&c)) == j2 ) ) {
                        x = (x << 1) | b;
                        y = (y << 1) | c;
                        quit = 1;
						break;
                }
            }
             if (quit == 1)
                break;
        }
    }
    if ( ( ((a11&x)^(a12&y)) == b1 ) && ( ((a21&x)^(a22&y)) == b2 ) ) {
        printf("Yes\n");
        printf("%lld\t%lld\n", x, y);
    }
    else {
        printf("No\n");
    }
    return 0;
}
