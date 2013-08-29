obj = start.o clock.o ddr.o nand.o main.o uart.o irq.o led.o
CC := arm-linux-gcc
flag := -nostdlib

nand.bin:$(obj)
	arm-linux-ld -Tnand.lds -o nand.elf $^
	arm-linux-objcopy -O binary -S nand.elf $@
	arm-linux-objdump -D nand.elf > nand.dis

%.o: %.c
	$(CC) $(flag) -c -o $@ $<
%.o: %.S
	$(CC) $(flag) -c -o $@ $<
 
clean:
	-rm -f *.o *.bin *.elf *.dis
