CC = gcc
CFLAGS = -O0 -Wall -lm -lpthread

all: schedDEADLINE schedNORMAL schedFIFO

schedDEADLINE: schedDEADLINE.c
	$(CC) -o $@ $< $(CFLAGS)

schedNORMAL: schedNORMAL.c
	$(CC) -o $@ $<

schedFIFO: schedFIFO.c
	$(CC) -o $@ $< $(CFLAGS)
