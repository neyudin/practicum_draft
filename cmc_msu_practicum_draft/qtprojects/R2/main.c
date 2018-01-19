#include <stdio.h>
#include<stdlib.h>
typedef int (* A) (int, int);
int F1 (int x, int y) {
    return x * y;
}
int F2 (int x, int y) {
    return x + y;
}
int F3 (int x, int y) {
    return x - y;
}
int F4 (int x, int y) {
    return x / y;
}
A function[6] = {F1, F2, 0, F3, 0, F4};
int main(void)
{
    int a, b;
    char c;
    scanf("%d%c%d", &a, &c, &b);
    printf("%d\n", function[(int)(c - 42)](a, b));
    return 0;
}
