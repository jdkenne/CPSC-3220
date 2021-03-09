#include <stdio.h>
#include "pthread.h"

static void *go(void * n);

#define NTHREADS 10
static pthread_t threads[NTHREADS];

int main(int argc, char* argv[]) {
	int i;
	for (i = 0; i < NTHREADS; i++) {
		printf("Hello from thread %d\n", i);
		pthread_create(&threads[i], NULL, &go, (void*)&i);
	}
	for (i = 0; i < NTHREADS; i++) {
		pthread_join(threads[i], NULL);
		printf("Thread %d return with %d\n", i, i+100);
	}
	printf("Main thread done.\n");
	return 0;
}

void *go(void *n) {
	pthread_exit(n);
}
