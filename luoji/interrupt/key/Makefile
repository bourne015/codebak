
CC      = arm-linux-gcc
LD      = arm-linux-ld
AR      = arm-linux-ar
OBJCOPY = arm-linux-objcopy
OBJDUMP = arm-linux-objdump

CFLAGS 		:= -Wall -O2 -fno-builtin-printf 
CPPFLAGS   	:= -nostdinc

export 	CC AR LD OBJCOPY OBJDUMP INCLUDEDIR CFLAGS CPPFLAGS 

objs := start.o  clock.o ddr.o irq.o key.o test.o

key.bin: $(objs)
	${LD} -Tkey.lds -o key.elf $^
	${OBJCOPY} -O binary -S key.elf $@
	${OBJDUMP} -D key.elf > key.dis

	
%.o:%.c
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

%.o:%.S
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	rm -f uart.bin uart.elf uart.dis *.o
	
