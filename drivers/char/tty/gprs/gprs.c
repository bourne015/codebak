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
	tty_writecmd("ath", strlen("ath"));//发送挂机命令ATH
}

void gprs_ans()
{ 
	tty_writecmd("at", strlen("at"));
	tty_writecmd("ata", strlen("ata"));//发送接听命令ATA
}

//拨叫  
void gprs_call(char *number, int num)			
{ 

	tty_write("atd", strlen("atd")); //发送拨打命令ATD	
	tty_write(number, num);
	tty_write(";\r", strlen(";\r"));
	usleep(200000);
}

//发送短信
void gprs_msg(char *number, int num)		
{ 
	char ctl[]={26,0};
	char text[]="Welcome to use up-tech embedded platform!";
	tty_writecmd("at", strlen("at"));
	tty_writecmd("at", strlen("at"));
	tty_writecmd("at+cmgf=1", strlen("at+cmgf=1"));		//发送修改字符集命令
	tty_write("at+cmgs=", strlen("at+cmgs="));	//发送发短信命令，具体格式见手册
	
	tty_write("\"", strlen("\""));
	tty_write(number, strlen(number));
	tty_write("\"", strlen("\""));	
	tty_write(";\r", strlen(";\r"));
	tty_write(text, strlen(text));
	tty_write(ctl, 1);
	usleep(300000);
}
