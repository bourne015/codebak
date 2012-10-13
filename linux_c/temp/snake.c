#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
//#include <time.h>
//#include <sys/types.h>
#include <pthread.h>
#include <string.h>

#define y 17
#define x 50

char locate[y][x];  //the location of '*'
int n = 0;		//the number we have ate
WINDOW *new_win;
int file_pipes[2];

void *mycreate()
{
	int r, f;
	int fr_pipe[2];
	int num;
	WINDOW *create_win;
	
	if (pipe(file_pipes) != 0) 
		printf("warning: failed to create a pipe!!!\n");
	

	num = read(file_pipes[0], fr_pipe, sizeof(2*fr_pipe[0]));
	//printw("%d", num);
	if (n == 0) 
		r = 15; f = 10;
	while (num > 0) {
		if ((fr_pipe[0] == r && fr_pipe[1] == f)) {
			r = rand()%17+1;
			f = rand()%50+1;
                	//wrefresh(create_win);
                	wrefresh(new_win);
			n++;
		}
		create_win = newwin(3, 3, r, f);
		mvwaddch(new_win, r, f, '@');
		if (n == 0)
     //           	wrefresh(create_win);
                	wrefresh(new_win);
		num = read(file_pipes[0], fr_pipe, sizeof(2*fr_pipe[0]));	
	}
	pthread_exit(NULL);
}

/*static void *key_wait()
{

}
*/
static void display(void)
{
	int i, j;
	for (i = 0; i < y; i++) {
		for (j = 0; j < x; j++)
			wprintw(new_win,"%c", locate[i][j]);
		wprintw(new_win, "\n");
	}
}

static void *keyscan()
{
	int key = 0;
	int to_pipe[2];
	int i = 0, j = 0;
	pthread_t thread[2];	
	//pthread_create(&thread[0], NULL, key_wait, NULL);
        while (1) 
	while ((key = getch()) != 'q') {
                n++;
                switch(key) {
                        case 'a': j--; break;
                        case 's': i++; break;
                        case 'd': j++; break;
                        case 'w': i--; break;
                        default:move(10, 22);
                                printw("%s", "wrong key");
                                break;
                        }
                
		if (i == y) i = 0;
                else if (i < 0) 
			i =y;
                
		if (j == x) j = 0;
                else if (j < 0) 
			j = x;
               // to_pipe[0] = i;
		//to_pipe[1] = j;
		if (key) {
			wclear(new_win);
                	//mvwaddch(new_win, i, j, '*');
			locate[i][j] = '*';
			display();
			//write(file_pipes[1], to_pipe, sizeof(2 * to_pipe[0]));
			//mycreate();
			//pthread_create(&thread[1], NULL, mycreate, NULL);
			wrefresh(new_win);
		}
		key = 0;
        }
	//pthread_exit(NULL);
}
int mycontrol(void)
{
	int res[2];
	pthread_t thread[2];
	
	keypad(new_win, TRUE);
	noecho();
	
	res[0] = pthread_create(&thread[0], NULL, keyscan, NULL);
	//res[1] = pthread_create(&thread[1], NULL, mycreate, NULL);
	if (res[0] != 0)// || res[1] != 0)
		printf("thread creation failed\n");
	
	pthread_join(thread[0], NULL);
	//pthread_join(thread[1], NULL);
	return 0;
}

int main()
{
	initscr();
	memset(locate, ' ', sizeof(locate));
	move(21, 15);
	printw("%s", "press 'A' 'S' 'D' 'W' to control");
	move(22, 15);
	printw("%s", "press 'q' to quit");
	refresh();

	/*create the boundary*/
	new_win = newwin(y + 2, x + 2, 2, 7);
	box(new_win, '|', '-');
	wrefresh(new_win);
	
	/*control move*/
	new_win = newwin(y, x, 3, 8);
	mycontrol();
	
	endwin();
	exit(1);
}
