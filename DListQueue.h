
#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H
#include "DoubleLinkedList.h"
#include <iostream>
using namespace std;

template <class type>
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

	DoubleLinkedList<type> myQueue;
};


template <class type>
DListQueue<type>::DListQueue()
{
	myQueue = new DoubleLinkedList<type>();
	numElements = 0;
}
template <class type>
DListQueue<type>::DListQueue(int max)
{	
	myQueue = new DoubleLinkedList<type>();
	numElements = 0;
	mSize = max;
}
template <class type>
DListQueue<type>::~DListQueue()
{
	//delete stuff
	delete myQueue;
}
template <class type>
void DListQueue<type>:: insertBack(type data)
{
	cout << "inside Queue Insert Back()" << endl;
	myQueue.insertBack(data);
	++numElements;
	cout << "came back from list insert Back" << endl;
}
template <class type>
type DListQueue<type>::removeFront()
{
	--numElements;
	return myQueue.removeFront();
}
template <class type>
type DListQueue<type>::peekFront()
{
	return myQueue.getFront();
}
template <class type>
type DListQueue<type>::peekBack()
{
	return myQueue.getBack();
}
template <class type>
int DListQueue<type>::getSize()
{
	if(myQueue.size != numElements)
		return -1;
	return numElements;
}
template <class type>
bool DListQueue<type>::isFull()
{
	return (numElements == mSize);	
}
template <class type>
bool DListQueue<type>::isEmpty()
{
	return (numElements == 0);
}
#endif