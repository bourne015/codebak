#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student
{
	char name[10];
	int goal;
} stu;

enum kind {full, empty, deleted};

typedef struct list
{
	struct student data;
	enum kind info;
} list;

typedef struct hash
{
	int count;
	list *listnode;
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
		hashtbl->listnode[i].info = empty;
	}

	return hashtbl;
}

int find_key(const char *key, hash *h)
{
	int pos, posnum = 0;
	
	pos = hashfunc(key, h->count);

	while (h->listnode[pos].info != empty &&
			strcmp(h->listnode[pos].data.name, key) != 0) {
	
		pos += 2*(++posnum) -1;	
		if (pos > h->count)
			pos -= h->count;
	}

	return pos;
}

int hash_insert(stu new, hash *h)
{
	int pos;

	pos = find_key(new.name, h);	
	if (h->listnode[pos].info != full) {
		h->listnode[pos].info = full;
		h->listnode[pos].data = new;
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
	list p;
	int i, pos;

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
			pos = find_key(key, h);
			p = h->listnode[pos];
			printf("%s, %d\n", p.data.name, p.data.goal);
			break;
		default:
			break;
		}
	}
}
