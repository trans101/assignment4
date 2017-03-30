
#ifndef INTNODE_H
#define INTNODE_H
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
	int getSize();
	void setSize(int s);
};

//___________________________________
//
//IMPLEMENTATION
//___________________________________
template <class type>
DoubleLinkedList<type>:: DoubleLinkedList()
{
	this->size = 0;
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

	}
	size++;
}
template <class type>
void DoubleLinkedList<type>:: insertFront(type data)
{

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
	}
	++size;
}
template <class type>
type DoubleLinkedList<type>:: removeFront()
{

	IntNode<type> *temp = front;


	type d;

 
	if(isEmpty())
	{
		cout << "Error: Can't removeFront() on empty queue." << endl;
		return temp->data;
		
	}
	//multiple items in list
	else if(temp->next != NULL)
	{
		d = temp->data;
	
		front = front->next;
		front->prev= NULL;
		delete temp;

	}
	//only one item of list
	else
	{

		d = temp->data;
		front = NULL;
		back = NULL;
		delete temp;
		//now list is empty
	}
	//delete current;
	--size;
	return d;
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
	if(this->size == 0)
	{
		
		return true;
	}
	return false;
}
template <class type>
type DoubleLinkedList<type>:: getFront()
{
	if(front != NULL)
		return front->data;
	return 0;
}
template <class type>
type DoubleLinkedList<type>:: getBack()
{
	if(back != NULL)
		return back->data;
	return 0;
}
template <class type>
int DoubleLinkedList<type>::getSize()
{
	return this->size;
}
template <class type>
void DoubleLinkedList<type>::setSize(int s)
{
	this->size = s;
}

#endif

