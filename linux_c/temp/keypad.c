#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define pw 256
#define na 256
int main()
{
	char name[na];
	char passwd[pw];
	const char *realpass = "12345";
	int i = 0;
	
	initscr();
	
	move(5, 10);
	printw("%s", "please login:");
	move(7, 10);
	printw("%s", "user name:");
	getstr(name);

	move(8, 10);
	printw("%s", "password:");
	refresh();
	
	cbreak();
	noecho();
		
	memset(passwd, '\0', sizeof(passwd));
	while(i < pw) {
		passwd[i] = getch();
		if (passwd[i] == '\n') break;
		move(8, 20 + i);
		//addch('*');
		printw("%c",'*');
		refresh();
		i++;
	}

	echo();
	nocbreak();
	
	move(11, 10);
	if (strncmp(realpass, passwd, strlen(realpass)) == 0)
		printw("%s", "correct");
	else {
		printw("%s", "wrong:");
		printw("%s", passwd);
	}
	refresh();
	sleep(2);
	
	endwin();
	exit(1);
}
