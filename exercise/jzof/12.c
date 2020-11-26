/*
 * 打印1到最大的n位数
 * 输入为n，输出为打印1-n
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reprint(char *a, int n, int index)
{
    int i;

    if (index == n-1) {
        printf("%s\n", a);
        return;
    }
    for (i = 0; i < 10; i++) {
        a[index+1] = '0' + i;
        reprint(a, n, index+1);
    }
}

void printmax(int n)
{
    int i;
    char *a;

    a = malloc(sizeof(char)*n + 1);
    memset(a, '0', n);
    a[n] = '\0';

    for (i = 0; i < 10; i++) {
        a[0] = '0' + i;
        reprint(a, n, 0);
    }
    free(a);
}

int main(void)
{
    int n;

    scanf("%d", &n);
    printf("n = %d\n", n);

    printmax(n);
    return 0;
}
