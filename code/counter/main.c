#include "common.h"

int main(void)
{
	char type;
	int i = 0;
	double op2;
	double output[MAX];
	
	to_polan(output);
	while (output[i] != '\0') {
		type = output[i];
		switch(type) {
			//case NUMBER:
			//	push(output[i]);
			//	break;
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
			case '\0':
				printf("result = %f\n", pop());
				break;
			default:
				push(output[i]);
				break;
			}
		i++;
	}
//	printf("result = %f\n", pop());

	return 0;
}

#define MAXVAL  100

static int sp = 0;
static double val[MAXVAL];

void push(double f)
{
        if (sp < MAXVAL)
                val[sp++] = f;
        else
                printf("error:stack full!!!\n");
}

double pop(void)
{
        if (sp > 0)
                return val[--sp];
        else {
                return 0.0;
        }
}
