#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student
{
	char name[10];
	int goal;
} stu;

typedef struct list
{
	struct student data;
	struct list *next;
} list;

typedef struct hash
{
	int count;
	list **listnode;
} hash;

int hashfunc(const char *key, int count)
{
	unsigned int val = 0;

	while (*key)
		val += (val << 5) + *key++;

	return val%count;
}

hash *hash_init(void)
{
	int i;
	hash *hashtbl;

	hashtbl = malloc(sizeof (hash));
	if (hashtbl == NULL) {
		printf("failed to malloc hashtbl\n");	
		return NULL;
	}
	
	hashtbl->count = 100;// change this
	
	hashtbl->listnode = malloc(hashtbl->count * sizeof (list));
	if (hashtbl->listnode == NULL) {
		printf("failed to malloc list\n");
		return NULL;
	}

	for (i = 0; i < hashtbl->count; i++) {
		hashtbl->listnode[i] = (list *)malloc(sizeof (list));
		if (hashtbl->listnode[i] == NULL) {
			printf("failed to malloc listnode\n");
			return NULL;
		} else {
			hashtbl->listnode[i]->next = NULL;
		}
	}

	return hashtbl;
}

list *find_key(const char *key, hash *h)
{
	list *p;
	list *l;

	l = h->listnode[hashfunc(key, h->count)];
	p = l->next;

	while (p != NULL && strcmp(p->data.name, key) != 0)
		p = p->next;

	return p;
}

int hash_insert(stu new, hash *h)
{
	list *p;
	list *l;

	p = find_key(new.name, h);	
	if (p == NULL) {
		p = malloc(sizeof(list));
		if (p== NULL) {
			printf("failed to malloc insert list\n");
			return -1;
		} else {
			l = h->listnode[hashfunc(new.name, h->count)];
			p->data = new;
			p->next = l->next;
			l->next = p;
		}
	}

	return 0;
}

static stu one[] = {
	[0] = {
		.name = "cat",
		.goal = 15,
	},
	[1] = {
		.name = "dog",
		.goal = 5,
	},
	[2] = {
		.name = "bird",
		.goal = 20,
	},
};

int main(void)
{
	hash *h;
	char ch;
	char key[10];
	list *p;
	int i;

	h = hash_init();

	while (1) {
		scanf("%c", &ch);
		
		switch (ch) {
		case '1':
			for (i = 0; i < 3; i++)
				hash_insert(one[i], h);
			break;
		case '2':
			printf("key: ");
			scanf("%s", key);
			p = find_key(key, h);
			printf("%s, %d\n", p->data.name, p->data.goal);
			break;
		default:
			break;
		}
	}
}
