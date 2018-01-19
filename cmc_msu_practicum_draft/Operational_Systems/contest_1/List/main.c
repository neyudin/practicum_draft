#include <stdio.h>
#include <stdlib.h>
#define SIZE 5

struct Info
{
    char name[16];
    int value;
};

int arr_size = SIZE;

struct Info arr[SIZE];

/**/

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

/**/

int main(void)
{
    int j;
    for (int i = 0; i < arr_size; ++i) {
        j = scanf("%d %c", &arr[i].value, &arr[i].name[0]);
        printf("yes\n");
    }
    solve();
    struct Item *cur = list;
    printf("\n");
    for (int i = 0; i < arr_size; ++i, ++j) {
        printf("%d %c | ", arr[i].value, arr[i].name[0]);
    }
    printf("\n");
    while(cur) {
        printf("%d %c | ", cur->info.value, cur->info.name[0]);
        cur = cur->next;
    }
    return 0;
}
