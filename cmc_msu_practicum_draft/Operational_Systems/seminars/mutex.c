#include <thread.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>

enum { N = 10 };

volatile int value = 10;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
volatile int order;

void *thread_func(void *ptr)
{
	int self = (int) (uintptr_t) (ptr);
	while (1) {
		/*
		while (1) {
			pthread_mutex_lock(&mutex);
			int local = order;
			pthread_mutex_unlock(&mutex);
			if (local == self) break;
			sched_yield();
		}
		*/
		//printf("%d %d\n", self, value);
		pthread_mutex_lock(&mutex);
		int local = value;
		++local;
		usleep(1);//race condition
		value = local;
		pthread_mutex_unlock(&mutex);
		printf("%d %d\n", self, local);
		//order = (order + 1) % N;
	}
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