obj := main.o to_polan.o
CC = gcc
all: go

go: $(obj)
	$(CC) -o go $(obj)

%.o: %.c %.h
	gcc $@ -o $<

clean:
	-rm *.o go
	
