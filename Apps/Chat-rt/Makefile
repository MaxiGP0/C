CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: server client client_gui

server: server.c common.h
	$(CC) $(CFLAGS) server.c -o server

client: client.c common.h
	$(CC) $(CFLAGS) client.c -o client -lpthread

client_gui: client_gui.c common.h
	$(CC) $(CFLAGS) client_gui.c -o client_gui -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

clean:
	rm -f server client client_gui
