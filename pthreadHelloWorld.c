#include <stdio.h>
#include <pthread.h>

#define N 5

void* helloWorld() {
	printf("Hello World\n");
	pthread_exit(NULL);
}

int main() {
	pthread_t p[N];
	for (int i = 0; i < N; i++) 
		pthread_create(&p[i], NULL, helloWorld, NULL);

	for (int i = 0; i < N; i++)
		pthread_join(p[i], NULL);

	return 0;
}