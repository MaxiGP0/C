CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: server client

server: server.c common.h
	$(CC) $(CFLAGS) server.c -o server

client: client.c common.h
	$(CC) $(CFLAGS) client.c -o client -lpthread

clean:
	rm -f server client
