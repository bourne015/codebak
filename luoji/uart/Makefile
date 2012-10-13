objs := start.o clock_init.o main.o uart.o printf.o
uart.bin: $(objs)
	arm-linux-ld -Ttext 0 -o uart.elf $(objs)
	arm-linux-objcopy -O binary uart.elf uart.bin

start.o: start.S
	arm-linux-gcc -o start.o -c start.S
clock_init.o: clock_init.c
	arm-linux-gcc -o clock_init.o -c clock_init.c
main.o:	main.c uart.h
	arm-linux-gcc -o main.o -c main.c
uart.o:	uart.c
	arm-linux-gcc -o uart.o -c uart.c
printf.o: printf.c
	arm-linux-gcc -o printf.o -c printf.c
	
clean:
	rm -rf *.o *.elf *.bin	
