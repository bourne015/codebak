#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>

int main()
{
	WINDOW *new_win, *new_win2;
	int x, y;
	char a_letter = 'a';
	initscr();
	/*start*/
	move(5, 5);
	printw("%s", "testing multiple windows");
	refresh();
	sleep(1);
	/*write the background*/
	for (y = 0; y < LINES - 1; y++) {
		for (x = 0; x < COLS - 1; x++) {
			mvwaddch(stdscr, y, x, a_letter);
			a_letter++;
			if (a_letter == 'z') a_letter = 'a';
		}
	}
	refresh();
	sleep(2);
	
	/*create a new windows*/
	new_win = newwin(10, 20, 5, 5);
	mvwprintw(new_win, 2, 2, "%s", "this is new win");
	mvwprintw(new_win, 5, 2, "%s", "noticee the wideth and longeh");
	wrefresh(new_win);
	sleep(2);
	
	/*rewrite the background*/
	a_letter = '0';
	for (y = 0; y < LINES - 1; y++) {
		for (x = 0; x < COLS - 1; x++) {
			mvwaddch(stdscr, y, x, a_letter);
			a_letter++;
			if (a_letter == '9')
				a_letter = '0';
		}
	}
	wrefresh(stdscr);
	sleep(2);
	
	/*create another windows*/
	new_win2 = newwin(10, 20, 8, 8);
	box(new_win2, '|', '-');
	mvwprintw(new_win2, 5, 2, "%s", "new new win");
	wrefresh(new_win2);
	sleep(2);
	
	/*display one by one*/
	touchwin(new_win);
	wrefresh(new_win);
	sleep(2);
	
	wclear(new_win);
	wrefresh(new_win);
	sleep(2);
	
	delwin(new_win);
	touchwin(new_win2);
	wrefresh(new_win2);
	sleep(2);
	
	delwin(new_win2);
	touchwin(stdscr);
	refresh();
	sleep(2);
	
	endwin();
	exit(1);
}
