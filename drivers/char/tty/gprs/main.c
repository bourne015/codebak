#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <pthread.h>
#include "tty.h"
#include "gprs.h"

#define FALSE		0
#define TRUE  		1

volatile int STOP=FALSE;
int GET_GPRS_OK=FALSE;
int baud=B9600;
int get_baudrate(int argc,char** argv);

char * cmd[20]={
		"at",
		"ate1",					//
		"at+chfa=1", 			//����ͨ��ͨ��Ϊ1,AT+CHFA �����л�������Ƶͨ��
		"at+clvl=100",			//�����ܻ����������, AT+CLVL ������Ե��������Ƶ�ź�����
		"at+cmic=1,10"			//����ͨ��1�Ļ�Ͳ����
};


void *keyshell(void *data);

/* modem input handler */
void *gprs_read(void *data)
{
	char c;
  	printf("\nread modem\n");
	
  	while (STOP==FALSE)
	{		
		tty_read(&c,1); 	
		printf("%c",c);	
	}

  	return NULL; 
}

int main(int argc,char** argv)
{
	int ok;
	pthread_t th_a, th_b, th_show;
	void * retval;

	if(argc < 2)
	{
		printf ("Default baudrate is 9600 bps. If not, please enter the baudrate as a parameter!\n");
	}
	else
	{
		baud=get_baudrate(argc, argv);
	}

	tty_init();

	pthread_create(&th_a, NULL, keyshell, 0);
	pthread_create(&th_b, NULL, gprs_read, 0);

	while(!STOP)
	{
		usleep(100000);
	}

	tty_end();
	return 0; 
}

int get_baudrate(int argc,char** argv)
{
	int v=atoi(argv[1]);
	switch(v)
	{
	case 4800:
		return B4800;
		
	case 9600:
		return B9600;
		
	case 19200:
		return B19200;
		
	case 38400:
		return B38400;
		
	case 57600:
		return B57600;
		
	case 115200:
		return B115200;
	default:
		return -1;
	 } 	 
}

