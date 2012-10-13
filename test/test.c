#include <stdio.h>

main()
{
	int i = 0;
	char te[20] = "nand test";

	while (te[i])
		printf("%c\n", te[i++]);
}
