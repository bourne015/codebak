TOPDIR = ../

EXTRA_LIBS += -lpthread -lncurses

EXEC =  ./gprs
#OBJS =  main-bak1.o 
OBJS =  tty.o gprs.o menu.o 
CC = arm-linux-gcc
LINK = /home/lingd/ncurses/lib
INCLUDE = /home/lingd/ncurses/include

all: $(EXEC)
$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)  $(EXTRA_LIBS) -L${LINK}
menu.o: menu.c
	$(CC) $(LDFLAGS) menu.c -c -o menu.o -I${INCLUDE}

install:
	$(EXP_INSTALL) $(EXEC) $(INSTALL_DIR)

clean:
	-rm -f $(EXEC) *.elf *.elf2flt *.gdb *.o *~
