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
	char te_buf[20] = "test!!!";
	
	while (te_buf[i])
		put_char(te_buf[i++]);
}
