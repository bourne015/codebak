#include "ncurses/curses.h"
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include "tty.h"
#include "gprs.h"

#define ENDMINITERM 27 /* ESC to quit miniterm */
#define FALSE		0
#define TRUE  		1

volatile int STOP=FALSE;
int GET_GPRS_OK=FALSE;
int baud=B9600;
unsigned long br=9600;

char * cmd[20]={
		"at",
		"ate1",					//
		"at+chfa=1", 			//设置通话通道为1,AT+CHFA 命令切换主副音频通道
		"at+clvl=100",			//设置受话器音量最大, AT+CLVL 命令可以调节输出音频信号增益
		"at+cmic=1,10"			//设置通道1的话筒增益
};

#define StartX 1
#define StartY 1

void initial()
{
	initscr();//开启curses模式
	cbreak();//开启cbreak模式
	nonl();//输入字符不需要，按回车表示结束
	noecho();//键盘输入无回现
	intrflush(stdscr, false);
	keypad(stdscr, true);//开启keypad
	refresh();//清屏
}

void menu()
{
	box(stdscr, '|', '-');
	
	attron(A_REVERSE);//开启反白模式
	mvaddstr(0, 20 ,"GPRS");//移到（0，20）位置，打印“management process simulation“
	attroff(A_REVERSE);//关闭反白模式
	
	mvaddstr(2, 19, "[1] give a call");
	mvaddstr(4, 19, "[2] respond a call");
	mvaddstr(6, 19, "[3] hold a call");
	mvaddstr(8, 19, "[4] send a message");
	mvaddstr(10, 19, "[5] exit");
}

void get_number(char *num, int n)
{
	int i;
	
	for (i=0; i<n-1; i++)
	{
		num[i] = getch();
		if (num[i] == '\r')
			break;
		else
			printw("%c", num[i]);
	}
	num[i] = '\0';
}

void *gprs_write(void *data)
{
	unsigned int cmd;
	char number[20]="10086";

	do
	{
		cmd = getch();
		mvprintw(12, 19, "                                                                      ");
		mvprintw(13, 19, "                            ");
		move(12, 19);
		switch (cmd)
		{
		case '1':
			mvprintw(12, 19, "you select to gvie a call, please input number:");	
			get_number(number, 20);
			gprs_call(number, strlen(number));
			mvprintw(13, 19, "calling......");	
			break;
		case '2':
			mvprintw(12, 19, "you select to answer a call");
			gprs_ans();
			mvprintw(13, 19, "answering.......");	
			break;
		case '3':
			mvprintw(12, 19, "you select to hold a call");
			gprs_hold();
			mvprintw(13, 19, "holding.......");
			break;
		case '4':
			mvprintw(12, 19, "you select to send a message, please input number:");	
			get_number(number, 20);
			gprs_msg(number, strlen(number));
			mvprintw(13, 19, "sending......");	
			break;
		case '5':
		case 27://esc键
			endwin();
			exit(1);
			break;
		default:
			mvprintw(12, 19, "Unknown command!\n");
			break;
		}
	}
	while(1);

	return NULL;
}

/* modem input handler */
void *gprs_read(void *data)
{
	int y = 18, x = 19;
	char c;
  	mvprintw(17, 19, "read modem: baudrate is %ld bps", br);
	
  	while (STOP==FALSE)
	{		
		tty_read(&c,1); 	
		if (c == '\0' || c == ' ')
			continue;
		mvprintw(18, x++, "%c", c);		
	}

  	return NULL; 
}

int get_baudrate(int argc,char** argv)
{
	int v=atoi(argv[1]);
	br = v;
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

int main(int argc,char** argv)
{
	int ok;
	pthread_t th_a, th_b, th_show;
	void * retval;

	if(argc < 2)
	{
		printf("Default baudrate is 9600 bps. If not, please enter the baudrate as a parameter\n");
	}
	else
	{
		baud=get_baudrate(argc, argv);
	}

	tty_init();
	initial();
	menu();

	pthread_create(&th_a, NULL, gprs_write, 0);
	pthread_create(&th_b, NULL, gprs_read, 0);

	while(!STOP)
	{
		usleep(100000);
	}

	tty_end();
	return 0;
}
