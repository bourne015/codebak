#include "uart.h"

int main(void)
{
	uart_init();

	while (1) {
		my_printf("hello, done!");
	}
}
