/*	
 *to compare all kinds of order er
 */
#include "order.h"

int main(void)
{
	int dat[MAX];

	if (create_data() < 0) {
		printf("create data error\n");
		goto err;
	}

	if (get_data(dat) < 0) {
		printf("get data error\n");
		goto err;
	}
	
//	insert(dat);
	msort(dat, 0, MAX-1);
//	shell(dat);
	
	display(dat);
	err:
		return -1;
}
