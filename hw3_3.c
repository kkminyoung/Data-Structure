#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef int element;
typedef struct ListNode {
	element data;
	struct ListNode *link;
}ListNode;

typedef struct {
	ListNode *head;
	ListNode *tail;
	int length;
}ListType;

ListType list1;

int init(ListType *list) {
	list->head = NULL;
	list->tail = NULL;
	return 0;
}


ListNode *createNode(element data) {
	ListNode *new_node;
	new_node = (ListNode *)malloc(sizeof(ListNode));
	new_node->data = data;
	new_node->link = NULL;
	return new_node;
}

//add_first
void add_first(ListType *list, element data) {
	ListNode *node;
	node = createNode(data);

	if (list->head == NULL) {
		list->head = node;
		list->tail = node;
	}
	else {
		node->link = list->head;
		list->head = node;
	}
	list->length++;
}

//add_last
void add_last(ListType *list, element data) {
	ListNode *node;
	node = createNode(data);
	if (list->head == NULL) {
		list->head = node;
		list->tail = node;
	}
	else {
		list->tail->link = node;
		list->tail = list->tail->link;
	}
	list->length++;
}

//delete_first
int delete_first(ListType *list) {
	int data = 0;
	if (list->head == NULL) {
		printf("List is empty \n");
		return -1;
	}
	else {
		data = list->head->data;
		list->head = list->head->link;
	}
	list->length--;
	return data;
}

//delete_last
int delete_last(ListType *list) {
	ListNode *node = list->head;
	ListNode *next = node->link;

	while (next != list->tail) { 
		node = next;
		next = node->link;
	}
	int retval = next->data;
	free(next);
	node->link = NULL;
}


ListNode *get_node_at(ListType *list, int pos) {
	int i;
	ListNode *tmp_node = list->head;
	if (pos < 0)
		return NULL;
	for (i = 0; i < pos; i++)
		tmp_node = tmp_node->link;
	return tmp_node;
}

void insert_node(ListNode **phead, ListNode *p, ListNode *new_node) {
	if (*phead == NULL) {
		new_node->link = NULL;
		*phead = new_node;
	}
	else if (p == NULL) {
		new_node->link = *phead;
		*phead = new_node;
	}
	else {
		new_node->link = p->link;
		p->link = new_node;
	}
}

void add(ListType *list, int pos, element data) {
	if (pos == 0) {
		add_first(list, data);
	}
	else if (pos == list->length) {
		add_last(list, data);
	}
	else {
		ListNode *p = list->head;
		int i = 0;

		while (i < pos) {
			p = p->link;
			i++;
		}
		ListNode *node;
		node = createNode(data);
		node->data = data;
		p = get_node_at(list, pos - 1);

		insert_node(&(list->head), p, node);
		list->length++;
	}

}



int is_empty(ListType *list) {
	if (list->head == list->tail == NULL)
		return 1;
}

int get_length(ListType *list) {
	return list->length;
}



void remove_node(ListNode **phead, ListNode *p, ListNode *removed)
{
	p->link = removed->link;
	free(removed);
}

void delete_(ListType *list, int pos) {
	ListNode *p = get_node_at(list, pos - 1);
	ListNode *removed = get_node_at(list, pos);
	remove_node(&(list->head), p, removed);

	list->length--;
}




element get_entry(ListType *list, int pos) {

	//First
	if (pos == 0) {
		if (list->length == NULL) {
			printf("empty\n");
			exit(0);
		}
		return list->head->data;
	}
	//Last
	else if (pos + 1 == list->length) {
		if (list->length == 1) {
			if (list->length == NULL) {
				printf("empty\n");
				exit(0);
			}
			return list->head->data;
		}
		else {
			return list->tail->data;
		}

	}

	//Middle
	else {
		ListNode * node = list->head;
		int i = 0;
		while (i < pos) {
			node = node->link;
			i++;
		}
		return node->data;


	}
}



void display(ListType *list) {
	ListNode *node;
	if (list->head == NULL) {
		printf("EMPTY LIST \n");
		return;
	}
	node = list->head;
	printf("List : ");
	while (node != NULL) {
		printf("%d", node->data);
		node = node->link;

		if (node != NULL)
			printf("->");
	}
	printf("\n");
}

int is_in_list(ListType *list, element item) {
	ListNode *p;
	p = list->head;
	while ((p != NULL)) {
		if (p->data == item)
			break;
		p = p->link;
	}
	if (p == NULL)
		return FALSE;
	else
		return TRUE;
}



int main() {

	ListType list1;
	init(&list1);
	add_first(&list1, 20);
	add_last(&list1, 30);
	add_first(&list1, 10);
	add_last(&list1, 40);
	add(&list1, 2, 70);
	display(&list1);
	delete_(&list1, 2);
	delete_first(&list1);
	delete_last(&list1);
	display(&list1);

	printf("%s\n", is_in_list(&list1, 20) == TRUE ? "TRUE" : "FALSE");
	printf("%d\n", get_entry(&list1, 1));
}