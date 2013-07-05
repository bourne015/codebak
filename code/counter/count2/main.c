#include "common.h"

int main(void)
{
	int type, i = 0;
	double op2;
	char s[MAX];
	
	while ((type = getop(s)) != EOF) {
		switch(type) {
			case NUMBER:
printf("push%f\n", atof(s));
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':printf("hit\n");
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
//			case 'e':
//				printf("result = %.8g\n", pop());
//				printf("result = %f\n", pop());
//				break;
			default:
				printf("error:unknow command\n");
				break;
		}
	while (s[i])
	printf("in main:%c \n", s[i++]);
	}
	printf("result = %f\n", pop());

	return 0;
}
