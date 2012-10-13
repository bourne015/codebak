led.bin: start.o main.o
	arm-linux-ld -T led.lds -o led.elf start.o main.o
	arm-linux-objcopy -O binary led.elf led.bin
	arm-linux-objdump -D led.elf > led.dis

start.o : start.S
	arm-linux-gcc -o start.o start.S -c

main.o : main.c
	arm-linux-gcc -o main.o main.c -c

clean:
	rm *.o led.elf led.bin led.dis -f
