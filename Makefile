CC=gcc
CFLAGS=-I.

hellomake: main.c 
	$(CC) -o findtreasure main.c