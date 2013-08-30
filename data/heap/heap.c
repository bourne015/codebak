#include <stdio.h>
#include <stdlib.h>

#define heap_head (-1)

typedef struct heap
{
	int capacity;
	int size;
	int  *data;
} heap;

heap *queue_init(int max_data)
{
	heap *h;

	h = malloc(sizeof (heap));
	if (h == NULL) {
		printf("failed to malloc heap\n");
		return NULL;
	}

	h->data = malloc((max_data + 1) * sizeof (h->data));
	if (h->data == NULL) {
		printf("failed to malloc heap data\n");
		return NULL;
	}
	
	h->capacity = max_data;
	h->size = 0;
	h->data[0] = heap_head;

	return h;
}

void heap_insert(int x, heap *h)
{
	int i;
	
	for (i = ++h->size; h->data[i/2] > x; i /= 2)
		h->data[i] = h->data[i/2];
	h->data[i] = x;
}

void heap_delet_min(heap *h)
{
	int i;
	int last_data;
	int child;

	last_data = h->data[h->size--];

	for (i = 1; i*2 < h->size; i = child) {
		child = 2*i;

		if (child != h->size && h->data[child] > h->data[child+1])
			child++;
		if (last_data > h->data[child])
			h->data[i] = h->data[child];
		else
			break;
	}
	h->data[child] = last_data;
}

void display(heap *h)
{
	int i;

	for (i = 1; i <= h->size; i++)
		printf("heap[%d] = %d\n", i, h->data[i]);
}

int main(void)
{	
	int max_data = 20;
	heap *h;
	int x;
	char ch;

	h = queue_init(max_data);

	while (1) {
		scanf("%c", &ch);
		switch (ch) {
		case '1':
			printf("input data: ");
			scanf("%d", &x);
			heap_insert(x, h);
			printf("insert done\n");
			break;
		case '2':
			heap_delet_min(h);
			break;
		case '3':
			display(h);
			break;
		case 'q':
			return 0;
		default:
			break;
		}
	}

	return 0;
}
