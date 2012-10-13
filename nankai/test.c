#include<stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int t, *a;
	float k;
	srand(time(NULL));
	//scanf("%d", &t);
	//a = malloc((t+1)*sizeof(int));
	//k = sqrt(t) * sqrt(t);
	//k = k * k;
	for (t = 0; t < 10; t++) {
		k = (float)(rand()%10+100)/10;
		printf("%f\n", k);
	}
}
