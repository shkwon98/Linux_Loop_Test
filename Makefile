CC = gcc
CFLAGS = -O0 -Wall -lm -lpthread

all: schedDEADLINE schedNORMAL schedFIFO

schedDEADLINE: schedDEADLINE.c
	$(CC) $(CFLAGS) -o $@ $<

schedNORMAL: schedNORMAL.c
	$(CC) -o $@ $<

schedFIFO: schedFIFO.c
	$(CC) $(CFLAGS) -o $@ $<