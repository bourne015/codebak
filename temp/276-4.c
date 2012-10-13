#include<stdio.h>

struct student {
	int num;
	float score;
	struct student *next;
};

struct student *creat() {
	struct student *head,*p1,*p2;
	int n=0;
	head=NULL;
	p1=(struct student *)malloc(sizeof(struct student));
	scanf("%d%f",&p1->num,&p1->score);
	while(p1->num!=0) {
		n++;
		if(n==1) 
			head=p1;
		else 
			p2->next=p1;
		p2=p1;
		p1=(struct student *)malloc(sizeof(struct student));
		scanf("%d%f",&p1->num,&p1->score);
		p1->next=NULL;
	}
	free(p1);
	return (head);
}	

struct student *insert(struct student *head) {
	int n=0;
	struct student *p,*p1,*p2;
	p=(struct student *)malloc(sizeof(struct student));
	scanf("%d%f",&p->num,&p->score);
	p1=head;
	if(head==NULL) {
		head=p;
		p->next=NULL;
	}	
	else {
		while(p->num>p1->num&&(p1->next!=NULL)) {
			p2=p1;
			p1=p1->next;
			n++;
		}
		if(head==p1) {
			p->next=head;
			head=p;
		}
		else if(p1->next==NULL&&n!=1) {
			p1->next=p;
			p->next=NULL;
		}
		else {
			p2->next=p;
			p->next=p1;
		}
	}
	return (head);
}

struct student *reverse(struct student *head)
{
	struct student *p1,*p2,*p;
	int n=0;
	p1=head;
	p2=p1;
	p=p1;
	p1=p1->next;
	while(p1!=NULL) {
		n++;
		//p1=p1->next;
		p=p1;
		if(n==1) {
			if(p1->next==NULL) {
		 		p1->next=p2;
				p2->next=NULL;
			}
			else p2->next=NULL;
		}
		p1=p1->next;
		p->next=p2;
		p2=p;
	}
//	tail->next=NULL;	
	return p;
}
void main()
{
	struct student *p,*p1,*p2,*p3,*p4;
	p=(struct student *)creat();
	p2=p;
	p3=p;
	(struct student *)output(p);
	printf("please insert a student:");
	p1=(struct student *)insert(p2);
	(struct student *)output(p1);
	p4=(struct student *)reverse(p1);
	printf("reverse order:\n");
	(struct student *)output(p4);
	
}

output(struct student *head)
{
	
	 
	while(head!=NULL) {
		printf("%d:  %.2f\n",head->num,head->score);
		head=head->next;
	}

}
