CC = gcc
CFLAGS = -Wall -Wextra -g `pkg-config --cflags gtk4`
LIBS = `pkg-config --libs gtk4`

TARGET = calculadora
SRCS = main.c funciones.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
