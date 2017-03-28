#include <iostream>
#ifndef DOUBLELINKEDLIST_H
using namespace std;

class DListQueue
{
public:
	DListQueue();
	DListQueue(int max);
	~DListQueue();

	void insertBack(int data); //enqueue
	int removeFront(); //dequeue
	int peekFront();
	int peekBack();


	int getSize();
	bool isFull();
	bool isEmpty();

	int head;
	int tail;

	int mSize;
	int numElements;

	DoubleLinkedList *myQueue;
};
#endif