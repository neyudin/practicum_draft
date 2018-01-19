#include<stdlib.h>

struct Item
{
    struct Item *next;
    struct Info info;
};

struct Item *list = NULL;

void solve(void)
{
    for (int i = 0; i < arr_size; ++i) {
        struct Item *node = calloc(1, sizeof(*node));
        node->info = arr[i];
        node->next = list;
        list = node;
    }
}

