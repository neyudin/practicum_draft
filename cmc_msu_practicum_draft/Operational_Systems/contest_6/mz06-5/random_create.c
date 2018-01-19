#include <stdlib.h>

struct RandomOperations;
struct RandomGenerator;

typedef struct RandomOperations
{
    int (*next) (struct RandomGenerator *);
    void (*destroy) (struct RandomGenerator *);
} RandomOperations;

typedef struct RandomGenerator
{
    int prev;
    RandomOperations *ops;
} RandomGenerator;

int
myrand(RandomGenerator *node)
{
    return node->prev = (1103515245 * node->prev + 12345) % 2147483648u;
}

void
myfree(RandomGenerator *node)
{
    free(node);
}

RandomOperations procedures = {.next = myrand, .destroy = myfree};

RandomGenerator
*random_create(int seed)
{
    RandomGenerator *node = calloc(1, sizeof(*node));
    node->prev = seed;
    node->ops = &procedures;
    return node;
}
