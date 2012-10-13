all: go
CC = gcc
CFLAGS = -g -O -Wall
go: 14.o create_num.o
	$(CC) -o go 14.o create_num.o
14.o: 14.c 14.h
create_num.o: create_num.c 14.h

clean:
	-rm -f *.o
