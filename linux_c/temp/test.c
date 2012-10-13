#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <curses.h>

char xy[10][10];
char a[10];
int main()
{
	int i, j;
	initscr();
	memset(xy, ' ',sizeof(xy));
	xy[1][3] = 'a';
	xy[1][4] = 'b';
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++)
			printw("%c", xy[i][j]);
		printw("\n");
	}
	
	refresh();
	sleep(2);
	endwin();
	return 0;
}
