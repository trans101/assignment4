
#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H
#include "DoubleLinkedList.h"
#include <iostream>
using namespace std;

template <typename type>
class DListQueue
{
public:
	DListQueue();
	DListQueue(int max);
	~DListQueue();

	void insertBack(type data); //enqueue
	type removeFront(); //dequeue
	type peekFront();
	type peekBack();


	int getSize();
	bool isFull();
	bool isEmpty();

	int mSize;
	int numElements;

	DoubleLinkedList<type> *myQueue;
};


template <typename type>
DListQueue<type>::DListQueue()
{
	myQueue = new DoubleLinkedList<type>();
	numElements = 0;
}
template <typename type>
DListQueue<type>::DListQueue(int max)
{	
	myQueue = new DoubleLinkedList<type>();
	numElements = 0;
	mSize = max;
}
template <typename type>
DListQueue<type>::~DListQueue()
{
	//delete stuff
	delete myQueue;
}
template <typename type>
void DListQueue<type>:: insertBack(type data)
{
	myQueue.insertBack(data);
	++numElements;
}
template <typename type>
type DListQueue<type>::removeFront()
{
	myQueue.removeFront();
	--numElements;
}
template <typename type>
type DListQueue<type>::peekFront()
{
	myQueue.getFront();
}
template <typename type>
type DListQueue<type>::peekBack()
{
	myQueue.getBack();
}
template <typename type>
int DListQueue<type>::getSize()
{
	if(myQueue->size != numElements)
		return -1;
	return numElements;
}
template <typename type>
bool DListQueue<type>::isFull()
{
	return (numElements == mSize);	
}
template <typename type>
bool DListQueue<type>::isEmpty()
{
	return (numElements == 0);
}
#endif