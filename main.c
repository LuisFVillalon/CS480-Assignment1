#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include "bots.h"

// Our semaphore
sem_t FLAG;
// Track number of lines
int lineNumber = 1;

/* Each thread performs the following*/
void *bot(void *arg) {
	// Thread's ID
	pthread_t tid = pthread_self();

	for (int i = 1; i < 8; i++) {
	/* 
		Periodically get the semaphore FLAG.
		Even thread number, every two seconds.
		Odd thread number, every three seconds. 
	*/
		if (tid % 2 == 0) {
			sleep(2);
		} else {
			sleep(3);
		}
		sem_wait(&FLAG);

		// Open the file QUOTE.txt and write the thread's id followed by a quote depending on even or odd status
		FILE *fp = fopen("QUOTE.txt", "a");
		if (tid % 2 == 0) {
			fprintf(fp,
				"%d Thread ID %d: \"Controlling complexity is the essence of computer programming.\" --Brian Kernighan\r\n",
				lineNumber,
				tid);
		} else {
			fprintf(fp,
				"%d Thread ID %d: \"Computer science is no more about computers than astronomy is about telescopes.\" --Edsger Dijkstra\r\n",
				lineNumber,
				tid);
		}
		lineNumber++;

		// Close the file and relase the semaphore FLAG
		printf("Thread %d is running\n", tid);
		fclose(fp);
		sem_post(&FLAG);
	}

	// Exit
	return NULL;
}

int main() {
	printf("bots\n");
	// Create a file name QUOTE.txt
	FILE *fp = fopen("QUOTE.txt", "w");
	// Our PID (process ID)
	fprintf(fp, "%d Process ID: %d\r\n", lineNumber, getpid());
	lineNumber++;
	// Close the file QUOTE.txt
	fclose(fp);

	/* 
		Initialize our semaphore:
			- &FLAG = addres of our semaphore
			- 0 = indicates thread cannot be shared with other processes
			- 1 = initial value, indicates one permit available 
	*/	
	sem_init(&FLAG, 0 , 1);

	// Hold IDs for threads
	pthread_t tids[7];
	
	for (int i = 1; i < 8; i++) {
		printf("Creating thread, in main(): %d\n", i);
		/*
			Create thread using POSIX version (pthread_create):
			- tids[i] = thread id (output parameter)
			- NULL = use default thread settings
			- bot = function the thread executes
		*/
		pthread_create(&tids[i], NULL, bot);
	}

	// POSIX (pthread_join) call for blocking/calling threads to complete their work
	for (int i = 1; i < 8; i++) {
		pthread_join(tids[i], NULL);
	}

	// Destroy our semaphore, exit gracefully
	sem_destroy(&FLAG);
	printf("Program completed.\n");
	return 0;
}
