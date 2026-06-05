/*
CS 480 - Operating Systems [2026 Summer Session]
Project: Assigment 1 - Chatbots with Threads & Semaphores
File: main.c

Team Members:
- Luis Villalon: cssc3169 
- Bobby Bavongkhoun: cssc3110

Description:
This program uses POSIX threads and a semahore to simulat seven chatbots writing mesages to a shared file.
Since multuple threads would run concurrently, a semaphore is used to ensure that only one thread can accesss QUOTE.txt at a time.
Each thread periodically writes it s ID and a quote based on whether the thread number is one or odd.
The program would then record the process ID, wait for all threads to finish, release the allocated resources, and then exit.
*/


#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include "main.h"

// Our semaphore
sem_t FLAG;
// Track number of lines
int lineNumber = 1;

/* Each thread performs the following*/
void *bot(void *arg) {
	// Thread's ID
	int id = *(int *)arg;

	// Run a total of 8 times 
	for (int i = 0; i < 8; i++) {
	/* 
		Periodically get the semaphore FLAG.
		Even thread number, every two seconds.
		Odd thread number, every three seconds. 
	*/
		if (id % 2 == 0) {
			sleep(2);
		} else {
			sleep(3);
		}
		sem_wait(&FLAG);
		// Open the file QUOTE.txt and write the thread's id followed by a quote depending on even or odd
		FILE *fp = fopen("QUOTE.txt", "a");
		if (id % 2 == 0) {
			fprintf(fp,
				"%d Thread ID %d: \"Controlling complexity is the essence of computer programming.\" --Brian Kernighan\r\n",
				lineNumber,
				id);
		} else {
			fprintf(fp,
				"%d Thread ID %d: \"Computer science is no more about computers than astronomy is about telescopes.\" --Edsger Dijkstra\r\n",
				lineNumber,
				id);
		}
		lineNumber++;

		// Close the file and release the semaphore
		printf("Thread %d is running\n", id);
		fclose(fp);
		sem_post(&FLAG);
	}

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
	int ids[7];
	for (int i = 0; i < 7; i++) {
		ids[i] = i + 1;
		printf("Creating thread, in main(): %d\n", ids[i]);
		/*
			Create thread using POSIX version (pthread_create):
			- tids[i] = thread id (output parameter)
			- NULL = use default thread settings
			- bot = function the thread executes

		*/
		pthread_create(&tids[i], NULL, bot, &ids[i]);
	}

	// POSIX (pthread_join) call for blocking/calling threads to complete their work
	for (int i = 0; i < 7; i++) {
		pthread_join(tids[i], NULL);
	}

	// Destroy our semaphore, exit gracefully
	sem_destroy(&FLAG);
	printf("Program completed.\n");
	return 0;
}
