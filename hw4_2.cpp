// Simulation.cpp : Defines the entry point for the console application.
//

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#define MAX_QUEUE_SIZE	100
#define BANK_STAFF_SIZE 2

#define FALSE 0
#define TRUE 1

typedef struct element {
	int id;
	int arrival_time;
	int service_time;
} element;	 	// Customer structure

typedef struct QueueType {
	element  queue[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;

typedef struct {
	int id;
	int waited_time;
	int service_total_time;
	int service_time;

	element customerIDserving;
	QueueType waitingQueue;
}ServerElement;

typedef struct {
	ServerElement queue[MAX_QUEUE_SIZE];
	int front, rear;
}ServerQueue;

ServerQueue serverQueue;
int serverCnt = 0;

double random() {
	return rand() / (double)RAND_MAX;
}

int duration = 10;
double arrival_prob = 0.7;
int max_serv_time = 5;
int clock;

int customers;
int served_customers;
int waited_time;

int is_empty(QueueType * q)
{
	return (q->front == q->rear);
}

int is_empty_Staff(ServerQueue *q)
{
	return (q->front == q->rear);
}


int is_full(QueueType * q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

int is_full_Staff(ServerQueue *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}


void enqueue(QueueType * q, element item)
{
	if (is_full(q))
		printf("Queue is full\n");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}

void enequeueStaff(ServerQueue *q, ServerElement item)
{
	if (is_full_Staff(q))
		printf("Server Queue is Full\n");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}



element dequeue(QueueType * q)
{
	if (is_empty(q))
		printf("Queue is empty\n");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}

ServerElement dequeStaff(ServerQueue *q) {
	if (is_full_Staff(q))
		printf("Server Queue is empty\n");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}


int is_customer_arrived()
{
	if (random() < arrival_prob)
		return true;
	else return false;
}

void insert_customer(int arrival_time, QueueType *q)
{
	element customer;

	customer.id = customers++;
	customer.arrival_time = arrival_time;
	customer.service_time = (int)(max_serv_time * random()) + 1;
	enqueue(q, customer);
	printf("Customer %d comes in %d minutes. Service time is %d minutes.\n", customer.id, customer.arrival_time, customer.service_time);
}

int remove_customer(ServerElement * serverElement)
{
	element customer;
	int service_time = 0;

	if (is_empty(&serverElement->waitingQueue)) return 0;
	customer = dequeue(&serverElement->waitingQueue);
	service_time = customer.service_time - 1;
	served_customers++;
	waited_time += clock - customer.arrival_time;

	serverElement->customerIDserving.id = customer.id;
	serverElement->customerIDserving.arrival_time = clock;
	serverElement->customerIDserving.service_time = customer.service_time;

	printf("Customer %d starts service in %d minutes. Wait time was %d minutes.\n", customer.id, clock, clock - customer.arrival_time);
	return service_time;
}

void print_stat()
{
	printf("Number of customers served = %d\n", served_customers);
	printf("Total wait time =% d minutes\n", waited_time);
	printf("Average wait time per person = %f minutes\n",
		(double)waited_time / served_customers);
	printf("Number of customers still waiting = %d\n", customers - served_customers);

	for (int i = serverQueue.front + 1; i <= serverQueue.rear; i++) {

		printf("-> [Staff %d]\n", serverQueue.queue[i].id);
		printf("Service total time : %d분\n", serverQueue.queue[i].service_total_time);
		printf("watied time : %d분\n", serverQueue.queue[i].waited_time);

		if (serverQueue.queue[i].customerIDserving.id > -1) {
			if (serverQueue.queue[i].service_time > 0) {
				printf("마감시간이므로 고객 %d님의 남은 업무 %d분은 다음 날로\n", serverQueue.queue[i].customerIDserving.id, serverQueue.queue[i].service_time);
			}
			else {
				printf("end\n");
			}
		}
		printf("\n");

	}

}


// Simulation program
void main()
{
	int service_time = 0;

	clock = 0;

	serverCnt = BANK_STAFF_SIZE;
	ServerElement serverElement[BANK_STAFF_SIZE];

	for (int i = 0; i < serverCnt; i++) {
		serverElement[i].id = i + 1;
		serverElement[i].waited_time = 0;
		serverElement[i].service_total_time = 0;
		serverElement[i].service_time = 0;

		serverElement[i].waitingQueue.front = 0;
		serverElement[i].waitingQueue.rear = 0;

		enequeueStaff(&serverQueue, serverElement[i]);
	}

	while (clock++ < duration) {
		printf("current time: %d분\n", clock);
		for (int i = 0; i < 3; i++) {
			if (is_customer_arrived()) {
				int insertFlag = FALSE;
				// 첫 번째 스태프부터 탐색
				for (i = serverQueue.front + 1; i <= serverQueue.rear; i++) {
					if (serverQueue.queue[i].customerIDserving.id == -1 && is_empty(&serverQueue.queue[i].waitingQueue)) {
						insert_customer(clock, &serverQueue.queue[i].waitingQueue);
						printf("Customer %d : %d Staff \n", serverQueue.queue[i].waitingQueue.queue[serverQueue.queue[i].waitingQueue.rear].id, i);
						insertFlag = TRUE;
						break;
					}
				}
				// 두번째로 전부 서비스 중인 경우, 제일 적은 줄로 이동함.
				if (!insertFlag) {
					int min = 0;
					int minIndex = 0;

					for (i = serverQueue.front + 1; i <= serverQueue.rear; i++) {
						if (serverQueue.queue[i].waitingQueue.rear - serverQueue.queue[i].waitingQueue.front <= min) {
							min = serverQueue.queue[i].waitingQueue.rear - serverQueue.queue[i].waitingQueue.front;
							minIndex = i;
							break;
						}
					}

					insert_customer(clock, &serverQueue.queue[minIndex].waitingQueue);
				}
			}
		}

		for (int i = serverQueue.front + 1; i <= serverQueue.rear; i++) {
			printf("[Staff %d]\n", serverQueue.queue[i].id);
			if (serverQueue.queue[i].service_time > 0) {
				if (serverQueue.queue[i].customerIDserving.id > -1) {
					printf("");
				}
				serverQueue.queue[i].service_time--;
				serverQueue.queue[i].service_total_time++;
			}
			else {
				// 현재 서비스가 끝남.
				// 현재 줄에 아무도 없고 양 옆 줄에 대기 사람이 있으면 불러들임!
				if (is_empty(&serverQueue.queue[i].waitingQueue)) {
					if (i == serverQueue.front + 1) {
						// 맨 첫 번째 큐는 2번째 줄 확인하고 불러들임
						if (!is_empty(&serverQueue.queue[i + 1].waitingQueue)) {
							enqueue(&serverQueue.queue[i].waitingQueue, dequeue(&serverQueue.queue[i + 1].waitingQueue));
						}
					}
					else if (i == serverQueue.rear) {
						// 맨 마지막 큐는 그 전 줄 확인하고 불러들임
						if (!is_empty(&serverQueue.queue[i - 1].waitingQueue)) {
							enqueue(&serverQueue.queue[i].waitingQueue, dequeue(&serverQueue.queue[i - 1].waitingQueue));
						}
					}
					else {
						// 그 둘이 아니라면, 랜덤으로 양 옆에 불러옴
						if (!is_empty(&serverQueue.queue[i - 1].waitingQueue)) {
							enqueue(&serverQueue.queue[i].waitingQueue, dequeue(&serverQueue.queue[i - 1].waitingQueue));
						}
						else if (!is_empty(&serverQueue.queue[i + 1].waitingQueue)) {
							enqueue(&serverQueue.queue[i].waitingQueue, dequeue(&serverQueue.queue[i + 1].waitingQueue));
						}
					}
				}


				serverQueue.queue[i].service_time = remove_customer(&serverQueue.queue[i]);

				if (serverQueue.queue[i].service_time == 0) {
					printf("대기 중\n");
					serverQueue.queue[i].waited_time++;
					serverQueue.queue[i].customerIDserving.id = -1;
				}
			}
		}
		printf("\n");
	}

	print_stat();

}
