#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>

int mutex=1, full=0, empty=10;
int x = 0;

void producer() {
	--mutex;

	++full;
	--empty;
	x++;
	printf("Producer produces %d item\n", x);

	++mutex;
}

void consumer() {
	--mutex;
	++empty;
	--full;

	printf("Consumer consumes %d item\n", x);
	x--;

	++mutex;
}

int main() {
	// only one thread can execute in the critical section, for parallel #pragma omp parallel
	#pragma omp critical

	for (int i = 1; i > 0; i++) {
		int n;
		printf("Enter your choice: 1. Producer 2. Consumer: ");
		scanf("%d", &n);
		switch(n) {
			case 1:
				if (mutex == 1 && empty != 0)
					producer();

				else 
					printf("Buffer is full\n");
				
				break;

			case 2: 
				if (mutex == 1 && full != 10)
					consumer();
				else
					printf("Buffer is empty\n");

				break;

			default: 
				printf("Invalid choice");
				return 0;
		}


	}

	return 0;
}