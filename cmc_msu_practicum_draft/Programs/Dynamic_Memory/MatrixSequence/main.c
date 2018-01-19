#include <stdio.h>
#include <stdlib.h>

long long **multiplication (long long **inputi, long long in_size, long long **inputj, long long divisor) {
    long long i, j, **result = (long long **) calloc(in_size * in_size, sizeof(long long)), k;
    for (i = 0; i < in_size; ++i) {
        result[i] = (long long *) calloc(in_size, sizeof(long long));
        for (j = 0; j < in_size; ++j) {
            for (k = 0; k < in_size; ++k) {
                result[i][j] += inputi[i][k] * inputj[k][j] % divisor;
            }
        }
    }
    return result;
}

long long **bin_power (long long in_size, long long **A, long long degree, long long divisor) {
    long long j;
    if (!degree) {
        long long **Matrix = (long long **) calloc(in_size * in_size, sizeof(long long));
        for (j = 0; j < in_size; ++j) {
            Matrix[j] = (long long *) calloc(in_size, sizeof(long long));
            Matrix[j][j] = 1;
        }
        return Matrix;
    }
    if (degree % 2) {
        return multiplication(bin_power(in_size, A, degree - 1, divisor), in_size, A, divisor);
    } else {
        long long **temp = bin_power(in_size, A, degree >> 1, divisor);
        return multiplication(temp, in_size, temp, divisor);
    }
}

int main(void)
{
    long long k, N, p, i, sum = 0;
    scanf("%lld%lld%lld", &k, &N, &p);
    long long *F = (long long *) calloc(k, sizeof(long long));
    for (i = 0; i < k; ++i) {
        scanf("%lld", &F[k - i - 1]);
    }
    long long **A = (long long **) calloc(k * k, sizeof(long long));
    for (i = 0; i < k; ++i) {
        A[i] = (long long *) calloc(k, sizeof(long long));
        scanf("%lld", &A[0][i]);
    }
    for (i = 0; i + 1 < k; ++i) {
        A[i + 1][i] = 1;
    }
    if (N > k) {
        A = bin_power(k, A, N - k, p);
        for (i = 0; i < k; ++i) {
            sum += A[0][i] * F[i];
        }
    } else {
        sum = F[k - N];
    }
    sum %= p;
    printf("%lld\n", sum);
    return 0;
}
