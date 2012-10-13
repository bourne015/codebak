led.bin: start.o clock_init.o
	arm-linux-ld -Ttext 0 -o led.elf start.o clock_init.o
	arm-linux-objcopy -O binary led.elf led.bin

start.o: start.S
	arm-linux-gcc -o start.o -c start.S
clock_init.o: clock_init.S
	arm-linux-gcc -o clock_init.o -c clock_init.S

clean:
	-rm -rf *.o led.elf led.bin led.dis
