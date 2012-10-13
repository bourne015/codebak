//#include "uart.h"

char inbuf[1024];

void my_printf(char inbuf[])
{
	int i = 0;
	
	while (inbuf[i])
		put_char(inbuf[i++]);
}

void test2(void)
{
	int i = 0;
	char te_buf[20] = "nand test";
	
	while (te_buf[i])
		put_char(te_buf[i++]);
}

void test_no_copy(void)
{
	int i = 0;
	char te_buf[40] = "test before copy code";
	
	while (te_buf[i])
		put_char(te_buf[i++]);
}

/*
void my_scanf()
{
	
}
*/
