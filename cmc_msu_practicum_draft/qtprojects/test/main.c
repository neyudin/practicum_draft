//heapsort from less to greater
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned long long compare_counter = 0, swap_counter = 0;

int compare(int *a, int *b) {
    ++compare_counter;
    if (*a < *b) return 1;
    else return 0;
}

void swap (int *a, int *b) {
    ++swap_counter;
    int temp = *a;
    *a = *b;
    *b = temp;
}

void make_tree(int *array, int root, int num) {
    int left = 2 * root + 1, right = left + 1, max_child = right;
    while (max_child < num) {
        if (right < num)
            if (compare(&array[right], &array[left]))
                max_child = left;
        if (compare(&array[root], &array[max_child]))
            swap(&array[root], &array[max_child]);
        else break;
        root = max_child;
        left = 2 * root + 1;
        right = left + 1;
        max_child = right;
    }
}

static void heapsort(int *array, int n) {
    int i;
    for (i = n/2 - 1; i >= 0; --i) {
        make_tree(array, i, n);
    }
    for (i = n - 1; i > 0; --i) {
        swap(&array[0], &array[i]);
        make_tree(array, 0, i);
    }
}

int main(void)
{
    int i, n;
    scanf("%d", &n);
    int array[n];
    //int *heap_array = malloc(sizeof(int) * 2147483647);
    printf("before sorting:\n");
    for (i = 0, srand(time(NULL)); i < n/*2147483647*/; printf("%d ", /*heap_*/array[i]), ++i)
        /*heap_*/array[i] = rand() - RAND_MAX/2;
    heapsort(/*heap_*/array, n/*2147483647*/);
    for (i = 0, printf("\nafter sorting:\n"); i < n/*2147483647*/; printf("%d ", /*heap_*/array[i]), ++i) {}
    printf("\nnumber of compares: %llu\nnumber of swaps: %llu", compare_counter, swap_counter);
    return 0;
}
