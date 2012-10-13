#include<stdio.h>
void main()
{
	char a[30],key,ch;
	int i,n=0,m=0;
	for(i=0; (ch=getchar())!='*'; i++) {
		n++;
		a[i]=ch;
	}
	printf("all : %d choose a char\n",n);
	scanf(" %c",&key);
	for(i=0; i<=n; i++) {
		if(a[i]==key) m++;
	}
	printf("%c:%d\n",key,m);
}
