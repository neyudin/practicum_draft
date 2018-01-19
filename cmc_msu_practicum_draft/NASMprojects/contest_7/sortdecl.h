#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifndef GUARD
	#define SORT(a, n) heapsort(a, n)
	#define ANOTHERSORT(a, n) selectionsort(a, n)
	#define GUARD
	extern unsigned long long compare_counter, swap_counter;
	extern unsigned long long timestamp(void);
	extern void swap(double *, double *);
	#ifdef COMPARE_CG
		#define COMPARE(a, b) compare_lg(a, b)
		extern int compare_lg(double *, double *);
	#else
		#define COMPARE(a, b) compare_gl(a, b)
		extern int compare_gl(double *, double *);
	#endif
	void generate_array(double *array_1, double *array_3, int size, int variant) {
    	int i;
    	switch (variant) {
        	case 0: {
            	for (i = 1, srand(time(NULL)), array_3[0] = -rand() * rand ()/(rand () + 5.0) - size, array_1[0] = array_3[0]; i < size; ++i) {
                	array_3[i] = array_3[i - 1] + rand()/(rand() + 5.0) + rand()%100;
                	array_1[i] = array_3[i];
            	}
            	break;
        	}
        	case 1: {
            	for (i = 1, srand(time(NULL)), array_3[0] = rand() * rand ()/(rand () + 5.0) + size, array_1[0] = array_3[0]; i < size; ++i) {
                	array_3[i] = array_3[i - 1] - rand()/(rand() + 5.0) - rand()%100;
                	array_1[i] = array_3[i];
            	}
            	break;
        	}
        	case 2: {
            	for (i = 0, srand(time(NULL)); i < size; ++i) {
                	array_3[i] = rand()/(rand() + 1.0) + rand() - RAND_MAX/2;
                	array_1[i] = array_3[i];
            	}
            	break;
        	}
        	case 3: {
            	for (i = 0, srand(time(NULL)); i < size; ++i) {
                	array_3[i] = rand() * rand()/(rand() * rand() + 1.0) + (rand() - RAND_MAX/2) * (rand() - RAND_MAX/2) * (rand() - RAND_MAX/2);
                	array_1[i] = array_3[i];
            	}
            	break;
        	}
    	}
	}
	void make_tree(double *array, int root, int num) {
    	int left = 2 * root + 1, right = left + 1, max_child = left;
    	while (max_child < num) {
        	if (right < num)
            	if (COMPARE(&array[left], &array[right]))
                	max_child = right;
        	if (COMPARE(&array[root], &array[max_child]))
            	swap(&array[root], &array[max_child]);
        	else break;
        	root = max_child;
        	left = 2 * root + 1;
        	right = left + 1;
        	max_child = left;
    	}
	}
	void heapsort(double *array, int n) {
    	int i;
    	for (i = n/2 - 1; i >= 0; --i)
        	make_tree(array, i, n);
    	for (i = n - 1; i > 0; --i) {
        	swap(&array[0], &array[i]);
        	make_tree(array, 0, i);
    	}
    	if ((n > 1) && COMPARE(&array[1], &array[0]))
        	swap(&array[0], &array[1]);
	}
	void selectionsort(double *array, int n) {
		for (int i = 0; i < n - 1; ++i) {
			int min = i;
			for (int j = i + 1; j < n; ++j)
				if (COMPARE(&array[j], &array[min]))
					min = j;
				swap(&array[i], &array[min]);
		}
	}
#endif