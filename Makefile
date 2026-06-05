########################################
#######  ASSIGNMENT 1 Makefile #########
########################################  
all: bots

bots: main.c main.h
    gcc main.c -o bots -lpthread

clean:
	rm -f bots QUOTE.txt

#######################[ EOF: Makefile ]############