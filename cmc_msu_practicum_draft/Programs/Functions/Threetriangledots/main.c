#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float length (float ax, float ay, float bx, float by) {
    return sqrtf((by - ay)*(by - ay) + (bx - ax)*(bx - ax));
}

float cor (float ab, float bc, float ac, float bx, float cx) {
    float rat = ab*bc/(ab+ac) ;
    if (bx < cx)
        return (bx + rat*(cx - bx))/1000000;
    if (bx > cx)
        return (bx - rat*(bx - cx))/1000000;
    else
        return bx/1000000;
}

int main(void)
{
    float ax, ay, bx, by, cx, cy, ab, bc, ac, a1x, a1y, b1x, b1y, c1x, c1y;
    scanf("%f%f\n", &ax, &ay);
    scanf("%f%f\n", &bx, &by);
    scanf("%f%f", &cx, &cy);
    ax *= 1000000;
    ay *= 1000000;
    bx *= 1000000;
    by *= 1000000;
    cx *= 1000000;
    cy *= 1000000;
    ab = length(ax, ay, bx, by);
    bc = length(bx, by, cx, cy);
    ac = length(ax, ay, cx, cy);
    a1x = cor(ab, bc, ac, bx, cx);
    a1y = cor(ab, bc, ac, by, cy);
    b1x = cor(bc, ac, ab, cx, ax);
    b1y = cor(bc, ac, ab, cy, ay);
    c1x = cor(ac, ab, bc, ax, bx);
    c1y = cor(ac, ab, bc, ay, by);
    printf("%.5f\t%.5f\n", c1x, c1y);
    printf("%.5f\t%.5f\n", a1x, a1y);
    printf("%.5f\t%.5f\n", b1x, b1y);
    return 0;
}
