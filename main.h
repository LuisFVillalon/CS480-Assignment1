/*
CS 480 - Operating Systems [2026 Summer Session]
Project: Assigment 1 - Chatbots with Threads & Semaphores
File: main.h

Team Members:
- Luis Villalon: cssc3169 
- Bobby Bavongkhoun: cssc3110

Description:
This header file contains the declarations, and definitions needed by the main.c, including the semaphore, shared variables, and thread function prototype.
*/

#ifndef BOTS_H
#define BOTS_H

#include <semaphore.h>

extern sem_t FLAG;
extern int lineNumber;

void *bot();

#endif
