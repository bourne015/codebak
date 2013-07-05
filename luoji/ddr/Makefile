objs := start.o main.o ddr.o clock.o test.o
led.bin: $(objs)
	arm-linux-ld -T led.lds -o led.elf $(objs)
	arm-linux-objcopy -O binary led.elf led.bin
	arm-linux-objdump -D led.elf > led.dis

%.o : %.S
	arm-linux-gcc -o $@ $< -c
%.o : %.c
	arm-linux-gcc -o $@ $< -c

clean:
	rm *.o led.elf led.bin led.dis -f
