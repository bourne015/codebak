#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/list.h>
#include<linux/slab.h>
struct student
{
	char name[20];
	int num;
	struct list_head list;
};
	
struct student *p;
struct student *t;
struct list_head s_list;
struct list_head *pos;
	
int list_init()
{
	int i=0;
	INIT_LIST_HEAD(&s_list);
	p=kmalloc(sizeof(struct student)*5,GFP_KERNEL);
	memset(p,0,sizeof(struct student)*5);
	for(i=0; i<5; i++) {
		sprintf(p[i].name,"student%d",i+1);
		p[i].num=i+1;
		list_add(&(p[i].list),&s_list);
	}
	list_for_each(pos,&s_list) {
		t=list_entry(pos,struct student,list);
		printk("<0>student %d name %s",t->num,t->name);
	}
	return 0;
}

void list_exit()
{
	int i;
	for(i=0; i<5; i++) {
		list_del(&(p[i].list));
	}
	kfree(p);
}

module_init(list_init);
module_exit(list_exit);
