led_key.bin: led_init.S led_key.c
	arm-linux-gcc -g -c -o led_init.o led_init.S
	arm-linux-gcc -g -c -o led_key.o led_key.c
	arm-linux-ld -Ttext 0x56000000 -g led_init.o led_key.o -o led_key_elf
	arm-linux-objcopy -O binary -S led_key_elf led_key.bin
	arm-linux-objdump -D -m arm led_key_elf > led_key_c.dis

clean:
	-rm -f led_key.bin led_key_elf *.o
