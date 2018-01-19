#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    double x1, x2, x3, y1, y2, y3;
    //char c;
    scanf("%lf%lf\n", &x1, &y1);
    scanf("%lf%lf\n", &x2, &y2);
    scanf("%lf%lf", &x3, &y3);
    //c = " ";
    //printf("%.4f%.4f", (x1+x2+x3)/3, (y1+y2+y3)/3);
    printf("%.4f\t", (x1+x2+x3)/3);
    printf("%.4f\n", (y1+y2+y3)/3);
    return 0;
}
