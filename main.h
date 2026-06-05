#ifndef BOTS_H
#define BOTS_H

#include <semaphore.h>

extern sem_t FLAG;
extern int lineNumber;

void *bot();

#endif
