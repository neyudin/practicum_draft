#include <stdio.h>
#include <stdlib.h>

long long scan (long long b) { //it is so close
    long long a = 0;
    scanf("%lld", &b);
    if (b != 0) {
        a = scan(a);
    } else {
        return 0;
    }
    printf("%lld\t", b);
    return b;
}

int main(void)
{
    long long c = 0;
    c = scan(c);
    return 0;
}
