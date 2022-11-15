#include <iostream>
#include <pthread.h>
#include <string.h>
using namespace std;

string str[2] =  { "Abhinav,LT4,121,CSE", "Siddharth,LT3,122,CSE" };

void* printInfo(void* i) {
	int* index = (int*)i;

	cout << "Printing information for process " << (*index)+1 << " : ";
	cout << str[(*index)];
	cout << endl;

	pthread_exit(NULL);
}

int main() {
	pthread_t pid[2];

	for (int i = 0; i < 2; i++) {
		pthread_create(&pid[i], NULL, printInfo, &i);
	}

	for (int i = 0; i < 2; i++) 
		pthread_join(pid[i], NULL);

	return 0;
}