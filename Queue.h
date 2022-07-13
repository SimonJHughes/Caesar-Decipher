#ifndef QUEUE_H
#define QUEUE_H
#include <stddef.h>
struct node
{
	int number;
	node *next;
	node(int number1, node *next1 = NULL)
	{
		number = number1;
		next = next1;
	}
};

class Queue
{
private:
	node *rear, *front;
	int counter;
public:
	Queue()
	{rear = NULL, front=NULL; counter = 0;}
	void enqueue(int);
	int dequeue();
	bool isEmpty() const;
	void clear();
	bool isFull();
	~Queue();
};
#endif