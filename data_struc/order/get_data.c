#include "order.h"

int get_data(void)
{
        FILE *fd;
        int i = 0;

        if ((fd = fopen("in.dat", "r")) == NULL)
                return -1;

        printf("\nat first the data is:\n");

        for (i = 0; i < MAX; i++) {
                fscanf(fd, "%d", &b[i]);
                printf("%d ", b[i]);
        }
        printf("\n\n");

        fclose(fd);
        return 0;
}

