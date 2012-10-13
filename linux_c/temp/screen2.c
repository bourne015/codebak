#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>

int main()
{
	const char witch_one[] = " first witch ";
	const char witch_two[] = " second witch ";
	const char *scan;
	
	initscr();
	move(5, 15);
	attron(A_BOLD);
	printw("%s", "Macbeth");
	attroff(A_BOLD);
	refresh();
	sleep(1);
	
	move(8, 15);
	attron(A_STANDOUT);
	printw("%s", "thunder and lightning");
	attroff(A_STANDOUT);
	refresh();
	sleep(1);

	//standout();
	move(10, 10);
	printw("%s", "when shall we meet again");
	move(11, 23);
	printw("%s", "in thunder, lightning, or in rain?");
	move(13, 10);
	printw("%s", "when the hurlyburly's done,");
	move(14, 23);
	printw("%s", "when the battle's lost and won");
	//standend();
	refresh();
	sleep(1);
	
	attron(A_DIM);
	scan = witch_one + strlen(witch_one) - 1;
	while(scan != witch_one) {
		move(10, 9);
		insch(*scan--);
	}
	scan = witch_two + strlen(witch_two) - 1;
	while(scan != witch_two) {
		move(13, 9);
		insch(*scan--);
	}
	attroff(A_DIM);
	refresh();
	sleep(1);
	
	move(LINES - 1, COLS -1);
	refresh();
	sleep(1);
	
	endwin();
	exit(1);
}
