/*	
 *to compare all kinds of order er
 */
#include "order.h"

int create_data(void)
{
        int i = 0;
        int tmp;

        FILE *fd;

        if ((fd = fopen("in.dat", "w")) == NULL)
                return -1;

        for (i = 0; i < MAX; i++) {
                tmp = rand()%30000;
                //printf("%d ", a[i]);
                fprintf(fd, "%d ", tmp);
        }

        fclose(fd);
        return 1;
}

int get_data(int *dat)
{
        FILE *fd;
        int i = 0;

        if ((fd = fopen("in.dat", "r")) == NULL)
                return -1;

        for (i = 0; i < MAX; i++) {
                fscanf(fd, "%d", &dat[i]);
        }

        fclose(fd);
        return 0;
}

void display(int *dat)
{
        int i;

        printf("after ordered:\n");
        for (i = 0; i < MAX; i++)
                printf("%d ", dat[i]);
        printf("\n\n");
}

int main(void)
{
	int dat[MAX];

	if (create_data() < 0) {
		printf("create data error\n");
		return -1;
	}
	if (get_data(dat) < 0) {
		printf("get data error\n");
		return -1;
	}
	
//	insert(dat);
//	msort(dat, 0, MAX-1);
	quick(dat, 0, MAX-1);
//	shell(dat);
	
//	display(dat);
}
