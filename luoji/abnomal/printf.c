//#include "uart.h"

char inbuf[1024];

void my_printf(char inbuf[])
{
	int i = 0;
	
	while (inbuf[i])
		put_char(inbuf[i++]);
}

void test_swi(void)
{
	int i = 0;
	char te_buf[20] = "test swi";
	
	while (te_buf[i])
		put_char(te_buf[i++]);
}
void test_undef(void)
{
	int i = 0;
	char te_buf[40] = "test undefine instruction";
	
	while (te_buf[i])
		put_char(te_buf[i++]);
}
/*
void my_scanf()
{
	
}
*/
