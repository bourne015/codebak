#include "order.h"

int create_data(void)
{
        int i = 0;
        FILE *fd;

        if ((fd = fopen("in.dat", "w+")) == NULL)
                return -1;

        for (i = 0; i < MAX; i++) {
                a[i] = rand()%30000;
                //printf("%d ", a[i]);
                fprintf(fd, "%d ", a[i]);
        }
        fclose(fd);

        return 1;
}


void display(void)
{
        int i;

        printf("after ordered:\n");
        for (i = 0; i < MAX; i++)
                printf("%d ", b[i]);
        printf("\n");
}

