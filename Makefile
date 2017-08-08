CC = gcc
CFLAGS = -W -Wall
TARGET = client server
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

client: client.o
	$(CC) $(CFLAGS) -o $@ $^
	rm $^

server: server.o
	$(CC) $(CFLAGS) -o $@ $^
	rm $^

.c.o:
	$(CC) $(CFLAGS) -c $^

clean:
	rm $(TARGET)
