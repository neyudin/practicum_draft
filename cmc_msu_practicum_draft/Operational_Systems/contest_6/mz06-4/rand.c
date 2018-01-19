#include <stdlib.h>

int
rand_range(int low, int high)
{
    double dist = rand()/(RAND_MAX + 1.0);
    return (int) (dist * (high - low)) + low;
}