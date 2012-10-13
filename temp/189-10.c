#include<stdio.h>
#include<string.h>
void main()
{
	char a[30],b[30];
	char ch,*p;
	int i,j,n=0,m=0;
	for(i=0; (ch=getchar())!='*'; i++) {
		n++;
		a[i]=ch;
	}
	for(j=0; j<n; j++)
		printf("%c",a[j]);
	
	printf("\n");
	for(i=0; (ch=getchar())!='*'; i++) {
		m++;
		b[i]=ch;
	}	
	for(j=0; j<m; j++)
		printf("%c",b[j]);
	printf("\n");
	p=strcat(a,b);
//	for(j=n; j<n+m; j++)
//		a[j]=b[j-n];
	for(j=0; j<=n+m+3;j++) 
		printf("%c",a[j]);
	printf("\n");

}
