#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include "bots.h"

sem_t FLAG;
int lineNumber = 1;

void *bot(void *arg) {

	int id = *(int *)arg;

	for (int i = 0; i < 8; i++) {

		if (id % 2 == 0) {
			sleep(2);
		} else {
			sleep(3);
		}

		sem_wait(&FLAG);


		FILE *fp = fopen("QUOTE.txt", "a");

		if (id % 2 == 0) {
			fprintf(fp,
				"%d Thread ID %d: \"Controlling complexity is the essence of computer programming.\" --Brian Kernighan\n",
				lineNumber,
				id);
		} else {
			fprintf(fp,
				"%d Thread ID %d: \"Computer science is no more about computers than astronomy is about telescopes.\" --Edsger Dijkstra\n",
				lineNumber,
				id);
		}
		lineNumber++;
		printf("Thread %d is running\n", id);

		fclose(fp);

		sem_post(&FLAG);
	}

	return NULL;
}

int main() {
	printf("bots\n");
	FILE *fp = fopen("QUOTE.txt", "w");
	fprintf(fp, "%d Process ID: %d\n", lineNumber, getpid());
	lineNumber++;
	fclose(fp);

	sem_init(&FLAG, 0 , 1);

	pthread_t tids[7];
	int ids[7];
	for (int i = 0; i < 7; i++) {
		ids[i] = i + 1;
		printf("Creating thread, in main(): %d\n", i + 1);
		pthread_create(&tids[i], NULL, bot, &ids[i]);
	}
	for (int i = 0; i < 7; i++) {
		pthread_join(tids[i], NULL);
	}

	sem_destroy(&FLAG);

	printf("Program completed.\n");

	return 0;
}
