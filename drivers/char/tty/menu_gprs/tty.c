#include <sys/types.h>                                                  
#include <sys/stat.h>                                                      
#include <fcntl.h>                                                       
#include <termios.h>                                                    
#include <stdio.h>    
#include <stdlib.h>
#include <string.h>

#define BAUDRATE B9600
#define COM "/dev/gprs_uart"

static int fd;
static struct termios oldtio,newtio;

int tty_end()
{
	close(fd);
}

int tty_read(char *buf,int nbytes)
{
	return read(fd,buf,nbytes);
}

int tty_write(char *buf,int nbytes)
{
	int i;
	for(i=0; i<nbytes; i++)
	{
		write(fd,&buf[i],1);
		usleep(100);
	}
	return tcdrain(fd);
}

int tty_writecmd(char *buf,int nbytes)
{
	int i;
	for(i=0; i<nbytes; i++)
	{
		write(fd,&buf[i],1);
		usleep(100);
	}
	write(fd,"\r",1);
	usleep(300000);
	return tcdrain(fd);
}

extern int baud;
int tty_init()
{
	fd = open(COM, O_RDWR );
	if (fd <0)
	{
	    	perror(COM);
	    	exit(-1);
  	}

	return 0;
}
