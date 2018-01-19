#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(void)
{
    int n, k;
    scanf("%d", &n);
    long double lenght [n], accelleration [n];;
    for (k = 0; k < n; ++k) {
        scanf("%L", &lenght [k]);
    }
    for (k = 0; k < n; ++k) {
        scanf("%L", &accelleration [k]);
    }
    long double time = sqrtl(2 * lenght [0]/accelleration [0]), time1 = 0.0000;
    long double velocity = sqrtl(2 * accelleration [0] * lenght [0]);
    for (k = 1; k < n; ++k) {
        if (abs((long long) (accelleration [k] - 0.0000)) < 0) {
            accelleration [k] = ((long double) abs((long long) (accelleration [k] * 10000.0)))/10000.0;
            time1 += (sqrtl(2 * accelleration [k] * lenght [k] + velocity * velocity) + velocity)/(accelleration [k]);
        }
        else { if (abs((long long) (accelleration [k] - 0.0000)) != 0) {
                time += (sqrtl(velocity * velocity + 2* accelleration [k] * lenght [k]) - velocity)/accelleration [k];
            } else {
                time += lenght [k]/velocity;
            }
        }
        velocity = sqrtl(2 * accelleration [k] * lenght [k] + velocity * velocity);
    }
    time -= time1;
    printf("%.4f\n", time);
    return 0;
}
