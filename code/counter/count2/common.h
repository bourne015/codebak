#include <stdio.h>
#include <stdlib.h>

#define MAX     100
#define NUMBER  '0'

int isdigit(int);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
int getop(char s[]);

char output[100];
//int count = 0;
