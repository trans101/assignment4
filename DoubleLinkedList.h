
#ifndef INTNODE_H
#define INTNODE_H

//#include "IntNode.h"
//___________________________________
//
//DECLARATION
//___________________________________
using namespace std;
template <class type>
class DoubleLinkedList
{

public:
	IntNode<type> *front;
	IntNode<type> *back;
	int size;

	DoubleLinkedList();
	~DoubleLinkedList();

	void insertFront(type data);
	void insertBack(type data);
	type removeFront();
	type removeBack();
	bool isEmpty();
	type getFront();
	type getBack();
};

//___________________________________
//
//IMPLEMENTATION
//___________________________________
template <class type>
DoubleLinkedList<type>:: DoubleLinkedList()
{
	size = 0;
	front = NULL;
	back = NULL;
}
template <class type>
DoubleLinkedList<type>:: ~DoubleLinkedList()
{
	while(!isEmpty())
	{
		removeFront();
	}
	delete front;
	delete back;
	
}
template <class type>
void DoubleLinkedList<type>:: insertBack(type data)
{
	++size;
	IntNode<type> *node = new IntNode<type>(data);
	//if empty then create it
	if(isEmpty())
	{
		front = node;
		back = node;
	}
	//if not empty then find node that pointer is null
	else
	{
		IntNode<type> *current = back;
		back = node;
		current->next = node;
		back->prev = current;
		back->next = NULL;
		delete current;
	}
}
template <class type>
void DoubleLinkedList<type>:: insertFront(type data)
{
	++size;
	IntNode<type> *node = new IntNode<type>(data);
	//if empty then create it
	if(isEmpty())
	{
		front = node;
		back = node;
	}
	//if not empty then find node that pointer is null
	else
	{
		IntNode<type> *current = front;
		front = node;
		current->prev = node;
		front->prev = NULL;
		front->next = current;
		delete current;
	}
}
template <class type>
type DoubleLinkedList<type>:: removeFront()
{
	if(isEmpty())
	{
		return NULL;
	}
	else if(size == 1)
	{
		back = front;
	}
	else
	{
		front->next->prev = NULL;
	}
	IntNode<type> *current = front;
	front = front->next;
	front->prev = NULL;
	
	type data =  current->data;
	//sdelete current;
	--size;
	return data;
}
template <class type>
type DoubleLinkedList<type>:: removeBack()
{
	if(isEmpty())
	{
		return NULL;
	}
	else if(size == 1)
	{
		back = front;
	}
	else
	{
		back->prev->next = NULL;
	}

	IntNode<type> *current = back;
	back = back->prev;
	back->prev = NULL;
	
	type data =  current->data;
	//delete current;
	--size;
	return data;
}
template <class type>
bool DoubleLinkedList<type>:: isEmpty()
{
	if(size == 0)
		return true;
	return false;
}
template <class type>
type DoubleLinkedList<type>:: getFront()
{
	if(front != NULL)
		return front->data;
	return NULL;
}
template <class type>
type DoubleLinkedList<type>:: getBack()
{
	if(back != NULL)
	 return back->data;
	return NULL;
}

#endif

