#include <stdio.h>
#include <stdlib.h>
#include <math.h>


char symbol;
int number;

int polish_prefix_notation(int anonymous)
{
    int e1, e2;
    if ( anonymous == '*') return polish_prefix_notation(number)*polish_prefix_notation(number);
    if (anonymous == '/') {
        e1 = polish_prefix_notation(number);
        e2 = polish_prefix_notation(number);
        return e1/e2;
    }
    if (scanf("%d",&number) == 0) {
        scanf("%c",&symbol);
        return polish_prefix_notation(symbol);
    }
    else
    return number;
}


int main(void)
{
    if (scanf("%d",&number) == 0) {
        scanf("%c",&symbol);
        printf("%d",polish_prefix_notation(symbol));
    }
    else
        printf("%d",number);
    return 0;
}
