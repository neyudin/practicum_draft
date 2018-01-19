#include <stdio.h>
#include <stdlib.h>

/*void swa (long long *a, long long *b) {
    long long t;
    t = *a;
    a = *b;
    *b = t;
}*/

long long gcd (long long a, long long b) {
	while (b) {
		a %= b;
		//swa(a,b);
		long long t;
        t = a;
        a = b;
        b = t;
	}
	return a;
}

int main(void)
{
    long long a, b, c, d, e;
    scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
    e = gcd(gcd(gcd(a,b),c),d);
    printf("%lld\n",e);
    return 0;
}
