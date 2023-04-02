#include <stdio.h>
#include <stdlib.h>
#define QUEUE_SIZE 10

int* queue;
int	front;			// ����
int	rear;			// �Ĵ�
int size = 1;

//ť�� ���� �������� Ȯ���ϴ� ����
int isEmpty() {
	if (front == rear) 
		return 1;
	else 
		return 0;
}

// ť�� ��ȭ �������� Ȯ���ϴ� ����
int isFull() {
	if (front == (rear + 1) % QUEUE_SIZE) 
		return 1;
	else 
		return 0;
}

int queueSize() {
	return(rear - front + QUEUE_SIZE) % QUEUE_SIZE;
}

// ������ top�� ���Ҹ� �����ϴ� ����
void enqueue(int item) {
	int* temp;

	if (isFull()) {
		printf(" Full QUEUE\n");
	}
	else {
		rear = (rear + 1) % QUEUE_SIZE;
		queue[rear] = item;
	}
}

int dequeue() {
	if (isEmpty()) {	// ť�� ���� ������ ���
		printf("\n\n Queue is Empty!!\n");
		return 0;
	}
	else
	{
		front = (front + 1) % QUEUE_SIZE;
		return queue[front];
	}
	return 0;
}

// ť�� ���Ҹ� ����ϴ� ����
void printQueue() {
	int i, maxi = rear;
	if (front >= rear) 
		maxi += QUEUE_SIZE;
	printf("Queue size is [%2d]= ", queueSize());

	for (i = front + 1; i <= maxi; i++)
		printf("%2d ", queue[i % QUEUE_SIZE]);
	printf("\n");
}

void main(void) {
	int i;
	queue = (int*)malloc(QUEUE_SIZE * sizeof(int));

	for (i = 0; i < 9; i++) enqueue(i + 1);
	printQueue();
	for (i = 0; i < 7; i++) dequeue();
	printQueue();
	for (i = 10; i < 19; i++) enqueue(i + 1);
	printQueue();

	free(queue);
	getchar();
}