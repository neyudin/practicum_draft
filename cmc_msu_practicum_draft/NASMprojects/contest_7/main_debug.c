#include "sortdecl.h"// external functions and variables are declared or stored here

int main(void) {
	int n, j;
	unsigned long long times;
	do {
		printf("please, enter the variant of test for double numbers arrays sorting:\n'1' - all elements are sorted\n'2' - all elements are sorted in inverse order\n'3' - random\n'4' - another random\n");
		scanf("%d", &j);
		printf("please, enter number of the elements\n");
		scanf("%d", &n);
			double *array_3 = calloc(sizeof(double), n), *array_1 = calloc(sizeof(double), n);
			generate_array(array_1, array_3, n, j - 1);
			for (j = 0, printf("before sorting:\n"); j < n; printf("%lf ", array_3[j]), ++j) {}
			compare_counter = 0;
			swap_counter = 0;
			times = timestamp();
			SORT(array_3, n);
			times = timestamp() - times;
			printf("\nHEAP SORT:\nnumber of compares: %llu\nnumber of swaps: %llu\ntimes: %llu\n", compare_counter, swap_counter, times);
			for (j = 0, printf("after HEAP sorting:\n"); j < n; printf("%lf ", array_3[j]), ++j) {}
			compare_counter = 0;
			swap_counter = 0;
			times = timestamp();
			ANOTHERSORT(array_1, n);
			times = timestamp() - times;
			printf("\nSELECTION SORT:\nnumber of compares: %llu\nnumber of swaps: %llu\ntimes: %llu\n", compare_counter, swap_counter, times);
			for (j = 0, printf("after SELECTION sorting:\n"); j < n; printf("%lf ", array_1[j]), ++j) {}
			free(array_1);
			free(array_3);
			printf("\nif you want to continue testing, enter '1'\n");
			scanf("%d", &j);
	} while (j == 1);
	return 0;
}