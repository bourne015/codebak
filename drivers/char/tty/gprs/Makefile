TOPDIR = ../

EXTRA_LIBS += -lpthread 

EXEC =  ./gprs
#OBJS =  main-bak1.o 
OBJS =  tty.o gprs.o keyshell.o main.o #$(TOPDIR)/keyboard/keyboard.o $(TOPDIR)/keyboard/get_key.o
CC = arm-linux-gcc

all: $(EXEC)


$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)  $(EXTRA_LIBS) 

install:
	$(EXP_INSTALL) $(EXEC) $(INSTALL_DIR)

clean:
	-rm -f $(EXEC) *.elf *.elf2flt *.gdb *.o *~
