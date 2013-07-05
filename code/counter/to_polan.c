#include "common.h"

//#define MAX	100

//char output[MAX];

int to_polan(double output[])
{
	char c[MAX];
	char stack[MAX];
	int i = 0, j = 0, t = 0, n = 0;
	char number[MAX];

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
				while ((c[i] <='9'&&c[i] >= '0')||c[i] == '.') {
					number[n++] = c[i++];
				}
				i--;
				n = 0;
				output[j++] = atof(number);
				break;
		}
		i++;
	}
	while (t > 0) {
		output[j++] = stack[t--];
	}	

/*
	i = 0;
	while (output[i] != '\0') {
		printf("in to_polan:%f", output[i]);
		i++;
	}
	printf("\n");
*/
}
