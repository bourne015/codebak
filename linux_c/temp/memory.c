#include <stdlib.h>

#define num 1024

int main()
{
	char *p;
	int i = 0;
	char *scan;	
	p = (char *)malloc(num);
	if (p == NULL) exit(EXIT_FAILURE);
	
	scan = p;
	while ((i++) < 1000) {
		*scan = '\0';
		scan++;
		//*p = '\0';
		//p++;
	}
	exit(EXIT_SUCCESS);
}
