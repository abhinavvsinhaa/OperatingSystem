#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // for sleep

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0

int state[N];
int phil[N] = {0, 1, 2, 3, 4};

sem_t mutex;
sem_t S[N];

// NOTE: if we remove sleep, then the program will continuously run in a very fast manner
// mutex S[N] has no effect over program

void test(int num) {
	if (state[num] == HUNGRY && state[(num+1)%N] != EATING && state[(num+4)%N] != EATING) {
		state[num] = EATING;
		// sleep(2);
		printf("Philospher %d is eating.\n",num+1);
		// sem_post(&S[num]);
	}
}

void take_fork(int num) {
	sem_wait(&mutex);
	state[num] = HUNGRY;
	printf("Philospher %d is hungry.\n", num+1);
	test(num);
	sem_post(&mutex);
	// sem_wait(&S[num]);
	// sleep(1);
}

void put_fork(int num) {
	sem_wait(&mutex);
	state[num] = THINKING;
	test((num+1)%5);
	test((num+4)%5);
	sem_post(&mutex);
}

void* philosopher(void* num) {
	while(1) {
		int* i = num;
		// sleep(1);
		take_fork(*i);
		// sleep(0);
		put_fork(*i);
	}
}

int main() {
	int i;
	pthread_t thread_id[N];

	// initialize semaphore
	sem_init(&mutex, 0, 1);

	for (i = 0; i < N; i++) 
		sem_init(&S[i], 0, 0);

	for (i = 0; i < N; i++) {
		pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
		printf("Philospher %d is thinking.\n", i+1);
	}

	for (i = 0; i < N; i++)
		pthread_join(thread_id[i], NULL);


}