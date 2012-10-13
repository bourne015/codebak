all: go
CC = gcc
#CFLAGS = -g
#CFLAGS = -O

go: main.o menu.o find.o delete.o display.o sort.o\
		add_create.o save.o
	$(CC) -o go main.o menu.o find.o delete.o sort.o\
		display.o add_create.o save.o

main.o: main.c stu_head.h
menu.o: menu.c stu_head.h
add_create.o: add_create.c stu_head.h
display.o: display.c stu_head.h
find.o : find.c stu_head.h stu_head.h
delete.o: delete.c stu_head.h
sort.o: sort.c stu_head.h
save.o: save.c stu_head.h

clean:
	-rm *.o
