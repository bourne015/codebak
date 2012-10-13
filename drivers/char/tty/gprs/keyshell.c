#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

char shell_s[]="\ngprs shell> ";

void *keyshell(void *data)
{
	char cmd[256]={0,};
	
	gprs_init();		//GPRS 初始化	
	
	printf("\n<gprs control shell>");
	printf("\n [1]  give a call");		
	printf("\n [2]  respond a call");		
	printf("\n [3]  hold a call");		
	printf("\n [4]  send a msg");
	printf("\n [5]  exit");
	printf("\n [*] help menu");
		
	while(1)
	{
		printf(shell_s);
		fflush(stdout);

		scanf("%s", cmd);
		printf("%s", cmd);
		printf("\r\n");				//显示必要的输出

		if(strncmp("1",cmd,1)==0)
		{
			printf("\nyou select to gvie a call, please input number:");	
			fflush(stdout);
			scanf("%s", cmd);
			gprs_call(cmd, strlen(cmd));
			printf("\ncalling......");		
		}
		else if(strncmp("2",cmd,1)==0)
		{
			gprs_ans();
			printf("\nanswering.......");	
		}
		else if(strncmp("3",cmd,1)==0)
		{
			gprs_hold();
			printf("\nhold a call");
		}
		else if (strncmp("4",cmd,1)==0)
		{
			printf("\nyou select to send a message, please input number:");	
			fflush(stdout);
			scanf("%s", cmd);
			gprs_msg(cmd, strlen(cmd));
			printf("\nsending......");	
		}
		else if (strncmp("5",cmd,1)==0)
		{
			printf("\nexit gprs\n");	
			exit(0);	
		}
		else if (strncmp("*",cmd,1)==0)
		{
			printf("\n<gprs control shell>");
			printf("\n [1]  give a call");
			printf("\n [2]  respond a call");		
			printf("\n [3]  hold a call");		
			printf("\n [4]  send a msg");
			printf("\n [5]  exit");
			printf("\n [*] help menu");
		}
		else if(cmd[0] != 0)
		{
			system(cmd);
		}
	}

	return NULL;		
}
