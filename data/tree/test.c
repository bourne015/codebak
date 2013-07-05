#include <stdio.h>
#include <stdlib.h>

#define MAX	30

double output[MAX];

int to_polan(void)
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
				while ((c[i] >= '0' && c[i] <= '9') || c[i] == '.') {
					number[n++] = c[i++];
				} 
				number[n] = '\0';
				while (number[n])
					printf("test..:%c\n", number[n++]);
				n = 0;
				printf("num:%f\n", atof(number));
				output[j++] = atof(number);
				i--;
				
				//output[j++] = c[i];
				break;
		}
		i++;
	}
	while (t > 0) {
		output[j++] = stack[t--];
	}	

	i = 0;
	while (output[i] != '\0') {
		printf("%f", output[i++]);
	}
	printf("\n");
}

int main(void)
{
	to_polan();
}
