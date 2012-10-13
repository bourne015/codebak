objs := start.o main.o ddr.o clock.o test.o
CC = arm-linux-gcc
led.bin: $(objs)
	arm-linux-ld -T led.lds -o led.elf $(objs)
	arm-linux-objcopy -O binary led.elf led.bin
	arm-linux-objdump -D led.elf > led.dis

%.o : %.S
	$(CC) -o $@ $< -c

%.o : %.c
	$(CC) -o $@ $< -c

clean:
	rm *.o led.elf led.bin led.dis -f
