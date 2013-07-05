#include <setjmp.h>
#include <stdio.h>

static jmp_buf jmpbuf;
static int globval;

static void f2(void)
{
	longjmp(jmpbuf, 1);
}

static void f1(int i, int j, int k, int l)
{
	printf("in f1():\n");
	printf("globval = %d, autoval = %d, regival = %d, volaval = %d, statval = %d\n", globval, i, j, k, l);
	
	f2();
}

int main(void)
{
	int autoval = 1;
	register int regival = 2;
	volatile int volaval = 3;
	static int statval = 4;
	globval = 0;

	if (setjmp(jmpbuf) != 0) {
		printf("after longjmp:\n");
		printf("globval = %d, autoval = %d, regival = %d,volaval = %d, statval = %d\n", globval, autoval,regival, volaval, statval);
		return 0;
	}

	globval = 10; autoval = 11; regival = 12; volaval = 13; statval = 14;

	f1(autoval, regival, volaval, statval);
}
