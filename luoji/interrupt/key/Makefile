CC      = arm-linux-gcc
LD      = arm-linux-ld
OBJCOPY = arm-linux-objcopy
OBJDUMP = arm-linux-objdump

objs := start.o clock.o ddr.o irq.o key.o uart.o nand.o led.o test.o

key.bin: $(objs)
	${LD} -Tkey.lds -o key.elf $^
	${OBJCOPY} -O binary -S key.elf $@
	${OBJDUMP} -D key.elf > key.dis

	
%.o:%.c
	${CC} -c -o $@ $<

%.o:%.S
	${CC} -c -o $@ $<

clean:
	rm -f *.bin *.elf *.dis *.o
	
