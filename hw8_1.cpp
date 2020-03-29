#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_ELEMENT 200
#define MAX_VERTICES 8
#define INF 10000

typedef struct element {
	int key;
} element;

typedef struct HeapType {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

void init(HeapType *h){
	h->heap_size = 0;
}

void insert_min_heap(HeapType *h, element item){
	int i;
	i = ++(h->heap_size);
	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item; 
}

void build_min_heap(HeapType *h)
{
	int half_size = h->heap_size / 2;

	for (int i = half_size; i >= 1; i--)
	{
		element temp = h->heap[i];
		int parent = i;
		int child = 2 * i;
		while (child <= h->heap_size)
		{
			if (child < h->heap_size && h->heap[child].key > h->heap[child + 1].key)
				child++;
			if (temp.key <= h->heap[child].key) break;

			h->heap[parent] = h->heap[child];
			parent = child;
			child *= 2;
		}
		h->heap[parent] = temp;
	}
}


// 1. Decrease_key_min_heap 
void Decrease_key_min_heap(HeapType *h, int i, element item)
{
	if (item.key >= h->heap[i].key){
		printf("error : new key is not smaller than current key");
		return;
	}

	while ((i != 1) && (item.key < h->heap[i / 2].key))
	{
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

// 2. Increase_key_min_heap
void Increase_key_min_heap(HeapType *h, int i, element item)
{
	if (item.key <= h->heap[i].key)
	{
		printf("error : new key is not larger than current key.\n");
		return;
	}

	int parent = i;
	int child = 2 * i;

	while ((child <= h->heap_size)){
		if ((child < h->heap_size) &&(h->heap[child].key) > h->heap[child + 1].key)
			child++;

		if (item.key <= h->heap[child].key) {
			break;
		}

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = item;
}


void printHeap(HeapType *h) {
	for (int i = 1; i <= h->heap_size; i++) {
		printf("%d ", h->heap[i].key);
	}
	printf("\n");
}

int main(void)
{
	HeapType h1;
	init(&h1);
	element e1 = { 1 };
	element e2 = { 4 };
	element e3 = { 2 };
	element e4 = { 7 };
	element e5 = { 5 };
	element e6 = { 3 };
	element e7 = { 3 };
	element e8 = { 7 };
	element e9 = { 8 };
	element e10 = { 9 };

	element ed = { 3 };
	element ei = { 10 };

	insert_min_heap(&h1, e1);
	insert_min_heap(&h1, e2);
	insert_min_heap(&h1, e3);
	insert_min_heap(&h1, e4);
	insert_min_heap(&h1, e5);
	insert_min_heap(&h1, e6);
	insert_min_heap(&h1, e7);
	insert_min_heap(&h1, e8);
	insert_min_heap(&h1, e9);
	insert_min_heap(&h1, e10);

	build_min_heap(&h1);

	printf("Min heap : ");
	printHeap(&h1);

	printf("Decrease Min heap : ");
	Decrease_key_min_heap(&h1, 4, ed);
	printHeap(&h1);

	printf("Increase Min heap : ");
	Increase_key_min_heap(&h1, 3, ei);
	printHeap(&h1);

	return 0;

}
