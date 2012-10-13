/*
	to compare all kinds of order er
*/
#include "order.h"

int main(void)
{
	int *array;

	if (create_data() < 0) {
		printf("create data error\n");
		goto err;
	}

	if (get_data() < 0) {
		printf("get data error\n");
		goto err;
	}
	
	/*1: insert*/
//	insert_order();

	/*2: shell*/
//	shell_data();
	
	/*3:merge*/
	array = malloc(MAX * sizeof(int));
	msort(array, 0, MAX - 1);
	free(array);

	display();
	err:
		return -1;
}
