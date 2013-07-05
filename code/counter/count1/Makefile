obj := main.o stack.o getop.o to_polan.o
CC = gcc
all: go

go: $(obj)
	$(CC) -o go $(obj)

%.o: %.c %.h
	gcc $@ -0 $<

clean:
	-rm *.o
	
