#include <thread.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

enum { N = 100000 };

void *thread_func(void *ptr)
{
	int self = (int) (uintptr_t) (ptr);
	printf("%d\n", self);
	sleep(1000);
	return NULL;

}

int main()
{
	pthread_t *ids = calloc(N, sizeof(ids[0]));

	pthread_attr_t attr;
	pthread_attr_init(&attr);

	pthread_attr_setstacksize(&attr, 16 * 1024);
	pthread_attr_setguardsize(&attr, 0);

	for (int i = 0; i < N; ++i) {
		int r = pthread_create(&ids[i], &attr, thread_func, (void *) (uintptr_t) (i));
		if (r > 0) {
			fprintf(stderr, "%d: error: %s\n", i + 1, strerror(r));
			exit(1);
		}
	}
	for (int i = 0; i < N; ++i) {
		pthread_join(ids[i], NULL);
	}
	pthread_attr_destroy(&attr);
	return 0;
}