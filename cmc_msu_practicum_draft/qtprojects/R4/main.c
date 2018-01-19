#include <stdio.h>
#include <stdlib.h>

int mask[5] = {0xffff, 0xff00ff, 0xf0f0f0f, 0x33333333, 0x55555555};

int main(void)
{
    int index;
    unsigned int number;
    unsigned char CL = 1;
    for (index = 4, scanf("%u", &number); index > -1; CL <<= 1, --index) {
        number = ((number & mask[index]) << CL) | ((number & ~mask[index]) >> CL);
    }
    printf("%u\n", number);
    return 0;
}

