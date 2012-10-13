#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>

int main(void)
{
	initscr();
	move(5, 15);
	printw("%s", "hello world");
	//printf("hello world");
	refresh();
	sleep(2);
	endwin();
	exit(1);
}
