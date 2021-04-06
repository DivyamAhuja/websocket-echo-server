CC=gcc
CFLAGS= -Wall

LINK_LIBS = -lpthread -lwebsockets

all:
	$(CC) $(CFLAGS) -o server $(wildcard *.c) $(LINK_LIBS)
