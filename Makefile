/*
CS 480 - Operating Systems [2026 Summer Session]
Project: Assigment 1 - Chatbots with Threads & Semaphores
File: MAKEFILE

Team Members:
- Luis Villalon: cssc3169 
- Bobby Bavongkhoun: cssc3110

Description:
Builds the bots executables and provides a target for removing the generated files.
*/

########################################
#######  ASSIGNMENT 1 Makefile #########
########################################  
all: bots

bots: main.c main.h
	gcc main.c -o bots -lpthread

clean:
	rm -f bots QUOTE.txt

#######################[ EOF: Makefile ]############
