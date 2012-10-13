objs := start.o main.o ddr.o clock.o
led.bin: $(objs)
	arm-linux-ld -T led.lds -o led.elf $(objs)
	arm-linux-objcopy -O binary led.elf led.bin
	arm-linux-objdump -D led.elf > led.dis

start.o : start.S
	arm-linux-gcc -o start.o start.S -c
clock.o : clock_init.S
	arm-linux-gcc -o clock.o clock_init.S -c

main.o : main.c
	arm-linux-gcc -o main.o main.c -c
ddr.o : ddr.c
	arm-linux-gcc -o ddr.o ddr.c -c

clean:
	rm *.o led.elf led.bin led.dis -f
