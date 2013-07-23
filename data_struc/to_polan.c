#include <stdio.h>
#include <stdlib.h>

#define MAX	30

char stack[MAX];

int to_polan(void)
{
	char c[MAX];
	char tmp[MAX];
	int i = 0, j = 0, t = 0;

	gets(c);
	while (c[i] != '\0' && c[i] != '\n') {
		switch(c[i]) {
			case '+':
			case '-':
				while ((tmp[t] == '*'||tmp[t] == '/' ||
					tmp[t] == '+' || tmp[t] == '-')) {
					stack[j] = tmp[t];
					j++;
					t--;
				}
				t++;
				tmp[t] = c[i];
				break;
			case '*':
			case '/':
				while ((tmp[t] == '*'||tmp[t] == '/')) {
					stack[j] = tmp[t];
					j++;
					t--;
				}
				t++;
				tmp[t] = c[i];
				break;
			case '(':
				t++;
				tmp[t] = c[i];
				break;
			case ')':
				while (tmp[t] != '(') {
					stack[j] = tmp[t];
					j++;
					t--;
				}
				t--;
				break;
			default: 
				if (c[i] > '0' && c[i] < '9') {
					stack[j] = c[i];
					j++;
				} else {
					printf("unknow symbol\n");
				}
				break;
		}
		i++;
	}
	while (t > 0) {
		stack[j] = tmp[t];
		t--;
		j++;
	}	

	i = 0;
	while (stack[i] != '\0') {
		printf("%c", stack[i]);
		i++;
	}
	printf("\n");
}

void jsval(void)
{
	int i = 0;

	while (stack[i] != '\0') {
		;
	}
	return;
}

int main(void)
{
	to_polan();
	jsval();
}
