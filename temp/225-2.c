#include<stdio.h>
#include<stdlib.h>

struct student
{
	int num;
	char name[10];
	int score;
	struct student *next;
};

struct student *input()
{
	int n = 0; 
	struct student *head,*p1,*p2;
	p1 = malloc(sizeof(struct student));
	//scanf("%d %s %d",&p1->num,p1->name,&p1->score);
	scanf("%d",&p1->num);
	while(p1->num != 0) {
		n++;
		scanf("%s %d",p1->name,&p1->score);
		fflush(stdin);
		if(n == 1) head = p1;
		p2 = p1;
		p1 = malloc(sizeof(struct student));
		//scanf("%d %s %d",&p1->num,p1->name,&p1->score);
		scanf("%d",&p1->num);
		p2->next = p1;
	}
	p2->next = NULL;
	return head;
}

void display(struct student *head)
{
	struct student *p1;
	p1 = head;
	while(p1 != NULL) {
		printf("%d  %s  %d\n",p1->num,p1->name,p1->score);
		p1 = p1->next;
	}
}
void main(void)
{
	struct student *head;
	head = (struct student *)input();
	display(head);
}
