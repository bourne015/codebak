#include <stdio.h>

int main(void)
{
	if (rename("go", "gogo") < 0)
		printf("error\n");

	return 0;
}
