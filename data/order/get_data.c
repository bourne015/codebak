#include "order.h"

int get_data(int *dat)
{
        FILE *fd;
        int i = 0;

        if ((fd = fopen("in.dat", "r")) == NULL)
                return -1;

        printf("\nat first the data is:\n");

        for (i = 0; i < MAX; i++) {
                fscanf(fd, "%d", &dat[i]);
                printf("%d ", dat[i]);
        }
        printf("\n\n");

        fclose(fd);
        return 0;
}
