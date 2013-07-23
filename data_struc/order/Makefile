CC = gcc
#object = main.o create_display.o  get_data.o  insert.o\
        merge.o  order.h  shell_data.o
object = main.o create_display.o  get_data.o merge.o  order.h

go:	$(object)
	$(CC) -o go $(object)

main.o: main.c order.h

create_display.o: create_display.c order.h

get_data.o: get_data.c order.h

#insert.o: insert.c order.h

merge.o: merge.c order.h

#shell_data.o: shell_data.c order.h

clean:
	-rm *.o
