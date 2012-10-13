#include <stdlib.h>
#include <unistd.h>
#include <curses.h>

int main()
{
	WINDOW *child_win;
	int y, x;
	int count;
	char a_letter = '1';
	
	initscr();
	
	for (y = 0; y < LINES; y++) {
		for (x = 0; x < COLS; x++) {
			mvwaddch(stdscr, y, x, a_letter);
			a_letter++;
			if(a_letter == '9') a_letter = '0';
		}
	}

	child_win = subwin(stdscr, 10, 20, 10, 10);
	scrollok(child_win, 1);
	touchwin(stdscr);
	refresh();
	sleep(1);

	werase(child_win);
	mvwprintw(child_win, 2, 0, "%s", "this is chilewin");
	wrefresh(child_win);
	sleep(1);

	for (count = 0; count < 15; count++) {
		wprintw(child_win, "%s", "this text will scrolling");
		wrefresh(child_win);
		sleep(1);
	}

	delwin(child_win);
	touchwin(stdscr);
	refresh();
	sleep(1);
	
	endwin();
	exit(1);
}
