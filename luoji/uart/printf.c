//#include "uart.h"

char inbuf[1024];

void my_printf(char inbuf[])
{
	int i = 0;
	
	while (inbuf[i])
		put_char(inbuf[i++]);
}

void test(void)
{
	int i = 0;
	char te_buf[20] = "no uart test";
	
	while (te_buf[i])
		put_char(te_buf[i++]);
}
void test_uart(void)
{
	int i = 0;
	char te_buf[20] = "test with uart";
	
	uart_init();
	while (te_buf[i])
		put_char(te_buf[i++]);
}
/*
void my_scanf()
{
	
}
*/
