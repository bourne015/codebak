#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX     100

//int isdigit(int);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
int getop(char s[]);
