#include <stdio.h>
#include <string.h>

int main(void)
{
    int i, s = 0;
    int a[9] = {1,1,2,2,3,3,4,5,5};
    
    s = a[0];
    for (i = 1; i < 9; i++)
        s ^= a[i];
    
    printf("%d\n", s);
}
