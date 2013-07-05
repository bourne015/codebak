#include <stdio.h>
#include <stdlib.h>

#define MAX	30

char output[MAX];

int to_polan(void)
{
	char c[MAX];
	char stack[MAX];
	int i = 0, j = 0, t = 0;

	gets(c);
	while (c[i] != '\0' && c[i] != '\n') {
		switch(c[i]) {
			case '+':
			case '-':
				while ((stack[t] == '*'||stack[t] == '/' ||
					stack[t] == '+' || stack[t] == '-')) {
					output[j++] = stack[t--];
				}
				stack[++t] = c[i];
				break;
			case '*':
			case '/':
				while ((stack[t] == '*'||stack[t] == '/')) {
					output[j++] = stack[t--];
				}
				stack[++t] = c[i];
				break;
			case '(':
				stack[++t] = c[i];
				break;
			case ')':
				while (stack[t] != '(') {
					output[j++] = stack[t--];
				}
				t--;
				break;
			default: 
			//	if (c[i] > '0' && c[i] < '9') {
					output[j] = c[i];
					j++;
			//	} else {
			//		printf("unknow symbol\n");
			//	}
			//	break;
		}
		i++;
	}
	while (t > 0) {
		output[j++] = stack[t--];
	}	

	i = 0;
	while (output[i] != '\0') {
		printf("%c", output[i++]);
	}
	printf("\n");
}

void jsval(void)
{
	int i = 0;

	while (output[i] != '\0') {
		;
	}
	return;
}

int main(void)
{
	to_polan();
//	jsval();
}
