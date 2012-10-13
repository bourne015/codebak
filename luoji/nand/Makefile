objs := start.o main.o ddr.o clock_init.o uart.o printf.o
led.bin: $(objs)
	arm-linux-ld -T led.lds -o led.elf $(objs)
	arm-linux-objcopy -O binary led.elf led.bin
	arm-linux-objdump -D led.elf > led.dis

%.o : %.S
	arm-linux-gcc -c -o $@ $<

%.o : %.c
	arm-linux-gcc -c -o $@ $<

clean:
	rm *.o led.elf led.bin led.dis -f
