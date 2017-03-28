#include <iostream>
#ifndef DLISTQUEUE_H
#ifndef DOUBLELINKEDLIST_H
using namespace std;

DListQueue::DListQueue()
{
	myQueue = new DoubleLinkedList();
	numElements = 0;
}
DListQueue::DListQueue(int max)
{	
	myQueue = new DoubleLinkedList();
	numElements = 0;
	mSize = max;
}
DListQueue::~DListQueue()
{
	//delete stuff
	delete myQueue;
}
void DListQueue:: insertBack(int data)
{
	myQueue->insertBack(data);
	++numElements;
}
int DListQueue::removeFront()
{
	myQueue->removeFront();
	--numElements;
}
int DListQueue::peekFront()
{
	myQueue->getFront();
}
int DListQueue::peekBack()
{
	myQueue->getBack();
}
int DListQueue::getSize()
{
	if(myQueue->size != numElements)
		return -1;
	return numElements;
}
bool DListQueue::isFull()
{
	return (numElements == mSize);	
}
bool DListQueue::isEmpty()
{
	return (numElements == 0);
}
#endif
#endif

