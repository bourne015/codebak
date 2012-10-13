#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "tty.h"
#include"gprs.h"
#include <string.h>


void gprs_init()
{ 
	int i;
	for(i=0; i<5; i++)
	{
		tty_writecmd(cmd[i], strlen(cmd[i])); 
	}
}

void gprs_hold()
{
	tty_writecmd("at", strlen("at"));
	tty_writecmd("ath", strlen("ath"));//���͹һ�����ATH
}

void gprs_ans()
{ 
	tty_writecmd("at", strlen("at"));
	tty_writecmd("ata", strlen("ata"));//���ͽ�������ATA
}

//����  
void gprs_call(char *number, int num)			
{ 

	tty_write("atd", strlen("atd")); //���Ͳ�������ATD	
	tty_write(number, num);
	tty_write(";\r", strlen(";\r"));
	usleep(200000);
}

//���Ͷ���
void gprs_msg(char *number, int num)		
{ 
	char ctl[]={26,0};
	char text[]="Welcome to use up-tech embedded platform!";
	tty_writecmd("at", strlen("at"));
	tty_writecmd("at", strlen("at"));
	tty_writecmd("at+cmgf=1", strlen("at+cmgf=1"));		//�����޸��ַ�������
	tty_write("at+cmgs=", strlen("at+cmgs="));	//���ͷ�������������ʽ���ֲ�
	
	tty_write("\"", strlen("\""));
	tty_write(number, strlen(number));
	tty_write("\"", strlen("\""));	
	tty_write(";\r", strlen(";\r"));
	tty_write(text, strlen(text));
	tty_write(ctl, 1);
	usleep(300000);
}
