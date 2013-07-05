#include "common.h"

int main(void)
{
	int type;
	double op2;
	char s[MAX];
	
	while ((type = getop(s)) != EOF) {
		switch(type) {
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if (op2 != 0.0)
					push(pop()/op2);
				else
					printf("zero error\n");
				break;
			case '\n':
				//printf("result = %.8g\n", pop());
				printf("result = %f\n", pop());
				break;
			default:
				printf("error:unknow command\n");
				break;
		}
	}
	
	return 0;
}
