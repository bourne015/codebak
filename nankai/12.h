#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <memory.h>
#define total 100

struct product
{
        char code[4];
        char name[10];
        int price;
        int num;
        long int all;
};

typedef struct product pro;
