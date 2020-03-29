// linked_stack.cpp : Defines the entry point for the console application.
//

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef int element;

typedef struct DlistNode {
	element data;
	struct DlistNode *llink;
	struct DlistNode *rlink;
} DlistNode;

typedef struct {
	DlistNode *top;
	DlistNode *head;
} LinkedStackType;

void init(DlistNode *phead, LinkedStackType *s) {
	phead->llink = phead;
	phead->rlink = phead;
	s->head = phead;
	s->top = s->head;
}

int is_empty(LinkedStackType *s)
{
	return (s->top == s->head);
}


void push(LinkedStackType *s, element data)
{
	DlistNode *temp = (DlistNode *)malloc(sizeof(DlistNode));
	if (temp == NULL) {
		fprintf(stderr, "Memory allocation error\n");
		return;
	}

	else {
		temp->data = data;
		temp->llink = s->top;
		temp->rlink = s->top->rlink;
		s->top->rlink->llink = temp;
		s->top->rlink = temp;
		s->top = temp;
	}
}

element pop(LinkedStackType *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "Stack is empty\n");
		exit(1);
	}
	else {
		DlistNode *temp = s->top;
		int data = temp->data;
		temp->llink->rlink = temp->rlink;
		temp->rlink->llink = temp->llink;
		s->top = s->top->llink;

		free(temp);
		return data;
	}
}

element peek(LinkedStackType *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "Stack is empty\n");
		exit(1);
	}
	else {
		return s->top->data;
	}
}


void main()
{
	DlistNode head_node;
	LinkedStackType s;
	init(&head_node, &s);
	push(&s, 1);
	push(&s, 2);
	push(&s, 3);

	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
}




