obj = start.o clock.o ddr.o nand.o main.o test.o uart.o
CC := arm-linux-gcc

nand.bin:$(obj)
	arm-linux-ld -Tnand.lds -o nand.elf $^
	arm-linux-objcopy -O binary -S nand.elf $@
	arm-linux-objdump -D nand.elf > nand.dis

%.o: %.c
	$(CC) -c -o $@ $<
%.o: %.S
	$(CC) -c -o $@ $<

clean:
	-rm -f *.o *.bin *.elf *.dis
