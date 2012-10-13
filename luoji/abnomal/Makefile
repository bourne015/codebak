objs := start.o clock_init.o main.o uart.o printf.o ddr.o
CC = arm-linux-gcc
uart.bin: $(objs)
	arm-linux-ld -T led.lds -o uart.elf $(objs)
	arm-linux-objcopy -O binary uart.elf uart.bin

%.o: %.S
	$(CC) -c -o $@ $<
%.o: %.c
	$(CC) -c -o $@ $<
	
clean:
	rm -rf *.o *.elf *.bin	
