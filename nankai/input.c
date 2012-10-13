#include "12.h"

int input(void)
{
        FILE *fd;
        int i = 0;
        pro pro1[total];
        fd = fopen("product12", "w");
        if (fd == NULL)
                return 0;
        printf("input some produces:\n");
        printf("code, name, price, num\n");
        scanf("%s", pro1[i].code);
        while (pro1[i].code[0] != 'q') {
		fflush(stdin);
                scanf("%s%d%d", pro1[i].name,
                        &pro1[i].price, &pro1[i].num);
                
		pro1[i].all = pro1[i].price * pro1[i].num;
               
		fwrite(&pro1[i], sizeof(pro[i]), 1, fd);
                i++;
		fflush(stdin);
                scanf("%s", pro1[i].code);
        }
        fclose(fd);
        return 1;
}

