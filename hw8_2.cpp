#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 8
#define INF 1000L
#define TRUE 1
#define FALSE 0

int weight[MAX_VERTICES][MAX_VERTICES] ={ 
	{ 0,3,INF,INF,INF,INF,INF,14 },
    { 3,0,8,INF,INF,INF,INF,10 },
    { INF,8,0,15,2,INF,INF,INF },
    { INF,INF,15,0,INF,INF,INF,INF },
    { INF,INF,2,INF,0,9,4,5 },
    { INF,INF,INF,INF,9,0,INF,INF },
    { INF,INF,INF,INF,4,INF,0,6 },
    { 14,10,INF,INF,5,INF,6,0 } 
};

typedef struct element {
	int key;
	int index;
} element;

typedef struct HeapType {
	element *heap;
	int heap_size;
} HeapType;

typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
}TreeNode;

void init(HeapType *h){
	h->heap_size = 0;
}

int is_empty(HeapType *h){
	if (h->heap_size == 0)
		return TRUE;
	else
		return FALSE;
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

element delete_min_heap(HeapType *h){
	int parent, child;
	element item, temp;
	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;

	while (child <= h->heap_size) {
		if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key)
			child++;

		if (temp.key <= h->heap[child].key) break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}

	h->heap[parent] = temp;
	return item;
}

void build_min_heap(HeapType *h){
	for (int i =h->heap_size/2; i >= 1; i--){
		element temp = h->heap[i];
		int parent = i;
		int child = 2 * i;
		while (child <= h->heap_size){
			if (child < h->heap_size && h->heap[child].key > h->heap[child + 1].key)
				child++;
			if (temp.key <= h->heap[child].key) 
				break;

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
	if (item.key >= h->heap[i].key) {
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

	while ((child <= h->heap_size)) {
		if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key)
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

void print_prim(int s, int n)
{
	int prim[8];
	int t_f[MAX_VERTICES];
	int parent_node[MAX_VERTICES];
	HeapType *h1 = (HeapType *)malloc(sizeof(HeapType));
	element e[MAX_VERTICES + 1];

	for (int i = 0; i <= n; i++){
		e[i].index = i - 1;
		e[i].key = INF;
	}
	for (int i = 0; i < n; i++){
		t_f[i] = FALSE;
		parent_node[i] = -1;	
	}
	e[s + 1].key = 0;
	h1->heap = e;
	h1->heap_size = MAX_VERTICES;
	build_min_heap(h1);

	for (int i = 0; i < n; i++){
		element u = delete_min_heap(h1);
		prim[u.index] = u.key;
		t_f[u.index] = TRUE;
		for (int v = 1; v <= h1->heap_size; v++){
			int v_index = e[v].index;
			if (weight[u.index][v_index] != INF){
				if (!t_f[v_index] && weight[u.index][v_index] < e[v].key){
					printf("")
					element ee = e[v];
					ee.key = weight[u.index][v_index];
					Decrease_key_min_heap(h1, v, ee);
					parent_node[v_index] = u.index;
				}
			}
		}
	}

	//Ãâ·Â(Specify the parent and child)
	for (int i = 1; i <= 7; i++) {
		printf("Vertex %d -> %d   edge : %d\n",parent_node[i], i, prim[i]);
	}
}

int main(void){
	print_prim(0, MAX_VERTICES);
	return 0;
}