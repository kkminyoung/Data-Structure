#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode
{
	int data;
	struct ListNode* link;
};

//체크
void display(struct ListNode* head)
{
	struct ListNode* p = head;
	while (p)
	{
		printf("%d -> ", p->data);
		p= p->link;
	}

	printf("NULL\n");
}

//list에 추가하기
void add_last(struct ListNode** phead, int data)
{
	struct ListNode* new_node = (struct ListNode*)malloc(sizeof(struct ListNode));
	new_node->data = data;
	new_node->link = *phead;
	*phead = new_node;
}

//이동
void MoveListNode(struct ListNode** destRef, struct ListNode** sourceRef)
{
	if (*sourceRef == NULL)
		return;

	struct ListNode* newListNode = *sourceRef;

	*sourceRef = (*sourceRef)->link;

	newListNode->link = *destRef; 
	*destRef = newListNode; 
}

//merge
struct ListNode* SortedMerge(struct ListNode* a, struct ListNode* b)
{
	struct ListNode dummy;
	dummy.link = NULL;

	struct ListNode* tail = &dummy;

	while (1)
	{
		if (a == NULL)
		{
			tail->link = b;
			break;
		}
		else if (b == NULL)
		{
			tail->link = a;
			break;
		}

		if (a->data <= b->data)
			MoveListNode(&(tail->link), &a);
		else
			MoveListNode(&(tail->link), &b);

		tail = tail->link;
	}

	return dummy.link;
}

int main(void)
{

	struct ListNode *a = NULL;
	struct ListNode *b = NULL;
	add_last(&a, 25);
	add_last(&a, 20);
	add_last(&a, 15);
	add_last(&a, 10);
	add_last(&a, 5);
	add_last(&a, 2);
	add_last(&a, 1);
	
	add_last(&b, 30);
	add_last(&b, 18);
	add_last(&b, 15);
	add_last(&b, 8);
	add_last(&b, 7);
	add_last(&b, 3);

	printf("a :  ");
	display(a);

	printf("b : ");
	display(b);

	struct ListNode* head = SortedMerge(a, b);
	printf("c : ");
	display(head);

	return 0;
}