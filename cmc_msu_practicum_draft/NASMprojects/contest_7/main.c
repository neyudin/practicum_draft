#include "sortdecl.h"// external functions and variables are declared or stored here

int main(void) {
	int sizes[6] = {10, 20, 50, 100, 1000, 10000}, j, k;
	unsigned long long compares[6][4][2], swaps[6][4][2], times[6][4][2];
	for (j = 0; j < 6; ++j) {
		for (k = 0; k < 4; ++k) {
			double *array_3 = calloc(sizeof(double), sizes[j]), *array_1 = calloc(sizeof(double), sizes[j]);
			generate_array(array_1, array_3, sizes[j], k);
			compare_counter = 0;
			swap_counter = 0;
			times[j][k][0] = timestamp();
			SORT(array_3, sizes[j]);
			times[j][k][0] = timestamp() - times[j][k][0];
			compares[j][k][0] = compare_counter;
			swaps[j][k][0] = swap_counter;
			compare_counter = 0;
			swap_counter = 0;
			times[j][k][1] = timestamp();
			ANOTHERSORT(array_1, sizes[j]);
			times[j][k][1] = timestamp() - times[j][k][1];
			compares[j][k][1] = compare_counter;
			swaps[j][k][1] = swap_counter;
			free(array_1);
			free(array_3);
		}
	}
	for (j = 0; j < 4; ++j) {
		printf("====================\t\t======\t\tsize of array is %d\t\t======\t\t====================:\n", sizes[j]);
		printf("\t\t\t\t\t\t\t<<<<<HEAP SORT>>>>>\t\t\t\t\t\t\t\narray  №:\t   \t1\t   \t2\t   \t3\t   \t4\t   \taverage\n");
		printf("compares:\t   \t%llu\t   \t%llu\t   \t%llu\t   \t%llu\t   \t%llu\n", compares[j][0][0], compares[j][1][0], compares[j][2][0], compares[j][3][0], (compares[j][0][0] + compares[j][1][0] + compares[j][2][0] + compares[j][3][0])/4);
		printf("swaps   :\t   \t%llu\t   \t%llu\t   \t%llu\t   \t%llu\t   \t%llu\n", swaps[j][0][0], swaps[j][1][0], swaps[j][2][0], swaps[j][3][0], (swaps[j][0][0] + swaps[j][1][0] + swaps[j][2][0] + swaps[j][3][0])/4);
		printf("time    :\t   \t%llu\t   \t%llu\t   \t%llu\t   \t%llu\t   \t%llu\n", times[j][0][0], times[j][1][0], times[j][2][0], times[j][3][0], (times[j][0][0] + times[j][1][0] + times[j][2][0] + times[j][3][0])/4);
		printf("\t\t\t\t\t\t\t<<<<<SELECTION SORT>>>>>\t\t\t\t\t\t\t\narray  №:\t   \t1\t   \t2\t   \t3\t   \t4\t   \taverage\n");
		printf("compares:\t   \t%llu\t   \t%llu\t   \t%llu\t   \t%llu\t   \t%llu\n", compares[j][0][1], compares[j][1][1], compares[j][2][1], compares[j][3][1], (compares[j][0][1] + compares[j][1][1] + compares[j][2][1] + compares[j][3][1])/4);
		printf("swaps   :\t   \t%llu\t   \t%llu\t   \t%llu\t   \t%llu\t   \t%llu\n", swaps[j][0][1], swaps[j][1][1], swaps[j][2][1], swaps[j][3][1], (swaps[j][0][1] + swaps[j][1][1] + swaps[j][2][1] + swaps[j][3][1])/4);
		printf("time    :\t   \t%llu\t   \t%llu\t   \t%llu\t   \t%llu\t   \t%llu\n", times[j][0][1], times[j][1][1], times[j][2][1], times[j][3][1], (times[j][0][1] + times[j][1][1] + times[j][2][1] + times[j][3][1])/4);
	}
	for (j = 4; j < 6; ++j) {
		printf("===================\t\t======\t\tsize of array is %d\t\t======\t\t====================:\n", sizes[j]);
		printf("\t\t\t\t\t\t\t<<<<<HEAP SORT>>>>>\t\t\t\t\t\t\t\narray  №:\t   \t1\t   \t2\t   \t3\t   \t4\t   \taverage\n");
		printf("compares:\t   \t%llu\t   \t%llu\t   \t%llu\t   \t%llu\t   \t%llu\n", compares[j][0][0], compares[j][1][0], compares[j][2][0], compares[j][3][0], (compares[j][0][0] + compares[j][1][0] + compares[j][2][0] + compares[j][3][0])/4);
		printf("swaps   :\t   \t%llu\t   \t%llu\t   \t%llu\t   \t%llu\t   \t%llu\n", swaps[j][0][0], swaps[j][1][0], swaps[j][2][0], swaps[j][3][0], (swaps[j][0][0] + swaps[j][1][0] + swaps[j][2][0] + swaps[j][3][0])/4);
		printf("time    :\t   \t%llu   \t%llu   \t%llu   \t%llu   \t%llu\n", times[j][0][0], times[j][1][0], times[j][2][0], times[j][3][0], (times[j][0][0] + times[j][1][0] + times[j][2][0] + times[j][3][0])/4);
		printf("\t\t\t\t\t\t\t<<<<<SELECTION SORT>>>>>\t\t\t\t\t\t\t\narray  №:\t   \t1\t   \t2\t   \t3\t   \t4\t   \taverage\n");
		printf("compares:\t   \t%llu   \t%llu   \t%llu   \t%llu   \t%llu\n", compares[j][0][1], compares[j][1][1], compares[j][2][1], compares[j][3][1], (compares[j][0][1] + compares[j][1][1] + compares[j][2][1] + compares[j][3][1])/4);
		printf("swaps   :\t   \t%llu\t   \t%llu\t   \t%llu\t   \t%llu\t   \t%llu\n", swaps[j][0][1], swaps[j][1][1], swaps[j][2][1], swaps[j][3][1], (swaps[j][0][1] + swaps[j][1][1] + swaps[j][2][1] + swaps[j][3][1])/4);
		printf("time    :\t   \t%llu   \t%llu   \t%llu   \t%llu   \t%llu\n", times[j][0][1], times[j][1][1], times[j][2][1], times[j][3][1], (times[j][0][1] + times[j][1][1] + times[j][2][1] + times[j][3][1])/4);
	}
	return 0;
}