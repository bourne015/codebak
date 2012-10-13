/***********************************************************

学生成绩管理系统
范涛
2012.4.25

************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<memory.h>

static int n=0;//用于计数节点（学生）个数
struct student {
	int num;
	char name[10];
	int score;
//	int aver;
	struct student *next;
};

struct student *create(void)
{
	struct student *head,*p1,*p2;
	head = NULL;
	p1 = malloc(sizeof(struct student));
	scanf("%d",&p1->num);
	while(p1->num != 0) {
		n++;
		scanf("%s %d",p1->name,&p1->score);
		if(n == 1)	head=p1;
		p2 = p1;
		p1 = malloc(sizeof(struct student));
		scanf("%d",&p1->num);
		p2->next = p1;
	}
	p2->next = NULL;
	free(p1);
	p1 = NULL;
	return head;
}

//2:display the SQL
void display(struct student *head)
{
	int n = 0;
	while(head != NULL) {// && head->num !=0) {
		printf("\t%d  %s  %d\n",head->num,head->name,head->score);
		head=head->next;
		n++;
	}
	printf("total:%d\n",n);
}

//8:open the SQL
struct student *open_SQL(void)
{
	FILE *fp;
	int n=0;
	struct student *buffer,*head,*p;
	if((fp=fopen("/home/fantao/myCODES/c/80-3.txt","r+"))==NULL) {
		printf("open error\n");
		exit(1);
	}
	while(!feof(fp)) {
		n++;
		buffer = (struct student *)malloc(sizeof(struct student));
		fread(buffer, sizeof(struct student), 1, fp);
		if (n == 1) {
			head = buffer;
			p = head;
		} 
		//if (buffer == EOF)
		//	break;
		else {
			head->next = buffer;
			head = head->next;
			head->next = NULL;
		}
	}
	free(buffer);
	printf("all:%d\n",n);
	//head->next = NULL;
	printf("\t%d  %s  %d\n",head->num,head->name,head->score);
	fclose(fp);
	return p;
}

//3:sort
struct student *sort(struct student *head)
{
	struct student *p1,*p2;
	int i, k = 0;
	p1 = malloc(sizeof(struct student));//创建空节点便于比较
	p1->next = head;
	head = p1;
	for(i=1; i<n; i++) {
		printf("here1\n");
		for(p1=head; p1->next->next!=NULL; p1=p1->next) {
			//printf("%d\n",p1->next->num);
			if(p1->next->num > p1->next->next->num) {
				printf("sort 1\n");
				p2=p1->next->next;
				p1->next->next=p2->next;
				p2->next=p1->next;
				p1->next=p2;
			}
		}
		return 0;
	}
	p1=head;
	head=head->next;//去除空节点
	free(p1);
	p1=NULL;
	printf("done!\n");
	display(head);		
        return head;	
}

//5:add a student
struct student *add(struct student *head)
{
	struct student *p1;
	char more;
	do {
		p1 = (struct student *)malloc(sizeof(struct student));
		scanf("%d%s%d",&p1->num,p1->name,&p1->score);
		//fflush(stdin);
		if (head == NULL) {
			head = p1;
			p1->next = NULL;
		}
		else{
			p1->next = head;	
			head = p1;
		}
		printf("do you want to add more,y/n? ");
		//more=getchar();
		scanf(" %c",&more);
	} while(more=='y'|| more=='Y');
	return head;
}

menu()
{
	int choice;
	printf("\n********************PB SQL*********************\n");
	printf("\t\t1:create a new PB SQL\n");
	printf("\t\t2:dislpay the SQL\n");
	printf("\t\t3:sort the  number\n");//按学号排序并显示
	printf("\t\t4:select a student\n");//搜索学号
	printf("\t\t5:add a student\n");
	printf("\t\t8:open the SQL\n");//打开已存在的表
	printf("\t\t9:save\n");
	printf("\t\to:quite\n");
	printf("********************PB SQL*********************\n");
	printf("choice:");
	scanf("%d",&choice);
	return choice;
}

//9:save	
void save(struct student *head)
{
	FILE *fp;
	if ((fp=fopen("/home/fantao/myCODES/c/80-3.txt","w+")) == NULL) {
		printf("failed to save\n");
		exit(1);
	}
	while(head != NULL && head->next != 0) {
		fwrite(head, sizeof(struct student), 1, fp);
		head = head->next;
	}
	printf("saved:%d\n",n);
	fclose(fp);
}

//4:select a student
void select_one(struct student *head)
{
	int choice;
	while(!scanf("%d",&choice));
	while(head!=NULL) {
		if(head->num==choice) 
			break;
		head=head->next;
	}
	printf("\t%d  %s  %d\n",head->num,head->name,head->score);	
}

int main(void)
{
	static struct student *head;//*p1,*p2;
	int choice;
	while(1) {
		choice=menu();
		switch(choice) {
		case 1:
			head=(struct student *)create(); 
			break;
		case 2:
			display(head);
			break;
		case 3:
			head=(struct student *)sort(head);
			break;
		case 4: 
			select_one(head);
			break;
		case 5:
			head=(struct student *)add(head);
			break;
		case 8:
			head=(struct student *)open_SQL();
			break;
		case 9:
			save(head); 
			break;
		case 0:
			return 0;
		default:printf("wrong choice\n");
			break;
		}
	}	
	return 0;
}

