#include "Queue.h"
#include <iostream>

using namespace std;

//Takes in an int and adds a node to the end of the queue with the input
void Queue::enqueue(int input)
{
	counter++;
	if(isEmpty())
	{
		front = new node(input);
		rear = front;
	}
	else
	{
		rear -> next = new node(input);
		rear = rear -> next;
	}
}

//Removes int from front of queue and returns it. Deletes the node.
int Queue::dequeue()
{
	counter--;
	node *temp = nullptr;
	int returnNum = 0;
	if(isEmpty())
	{
		return returnNum;
	}
	else
	{
		returnNum = front -> number;
		temp = front;
		front = front -> next;
		delete temp;
	}
	return returnNum;
}

//Returns true if empty and false if queue is not empty
bool Queue::isEmpty() const
{
	if(front == nullptr)
	{
		return true;
	}
	return false;
}

//Returns true if there are more than 100 items in queue and false if there are not
bool Queue::isFull()
{
	if(counter < 100)
	{
		return false;
	}
	return true;
}

//Clears the queue
void Queue::clear()
{
	while(!(isEmpty()))
	{
		dequeue();
	}
}

//Queue deconstructor
Queue::~Queue()
{
	node *tempNode = front;
	while(tempNode != nullptr)
	{
		front = front -> next;
		tempNode -> next = nullptr;
		delete tempNode;
		tempNode = front;
	}
}