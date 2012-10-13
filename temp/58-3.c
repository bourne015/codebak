#include<stdio.h>
#define num 3
struct
{
	char name[10];
	float price;
} books[num];

void sort()
{
	int i,j;
//	struct *p = books;
	char t;
	for(j=0; j<num-1; j++)
	for(i=0; i<num-1; i++) {
		if(books[i].name[0] > books[i+1].name[0]) {
			t = books[i].name[0];
			books[i].name[0] = books[i+1].name[0];
			books[i+1].name[0] = t;
		}
	}
//	return *p
}

void main()
{
	int j;
	for(j=0; j<num; j++)
		scanf("%s%f",books[j].name, &books[j].price);	
	sort();
	for(j=0; j<num; j++)
		printf("%s:%.2f\n",books[j].name, books[j].price);	
	
}
