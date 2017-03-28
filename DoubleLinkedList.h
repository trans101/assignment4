//___________________________________
//
//DECLARATION
//___________________________________
using namespace std;

class IntNode
{
public:
	int data;

	IntNode(int d);
	~IntNode();

	IntNode *next;
	IntNode *prev;

};
class DoubleLinkedList
{
public:
	IntNode *front;
	IntNode *back;
	int size;

	DoubleLinkedList();
	~DoubleLinkedList();

	void insertFront(int data);
	void insertBack(int data);
	int removeFront();
	int removeBack();
	bool isEmpty();
	int getFront();
	int getBack();
};

//___________________________________
//
//IMPLEMENTATION
//___________________________________

IntNode:: IntNode(int d)
{
	data = d;
	next = NULL;
	prev = NULL;
}
IntNode:: ~IntNode()
{

}
DoubleLinkedList:: DoubleLinkedList()
{
	size = 0;
	front = NULL;
	back = NULL;
}
DoubleLinkedList:: ~DoubleLinkedList()
{
	while(!isEmpty())
	{
		removeFront();
	}
	delete front;
	delete back;
	
}
void DoubleLinkedList:: insertBack(int data)
{
	++size;
	IntNode *node = new IntNode(data);
	//if empty then create it
	if(isEmpty())
	{
		front = node;
		back = node;
	}
	//if not empty then find node that pointer is null
	else
	{
		IntNode *current = back;
		back = node;
		current->next = node;
		back->prev = current;
		back->next = NULL;
		delete current;
	}
}
void DoubleLinkedList:: insertFront(int data)
{
	++size;
	IntNode *node = new IntNode(data);
	//if empty then create it
	if(isEmpty())
	{
		front = node;
		back = node;
	}
	//if not empty then find node that pointer is null
	else
	{
		IntNode *current = front;
		front = node;
		current->prev = node;
		front->prev = NULL;
		front->next = current;
		delete current;
	}
}
int DoubleLinkedList:: removeFront()
{
	if(isEmpty())
	{
		return -1;
	}
	else if(size == 1)
	{
		back = front;
	}
	else
	{
		front->next->prev = NULL;
	}
	IntNode *current = front;
	front = front->next;
	front->prev = NULL;
	
	int data =  current->data;
	delete current;
	--size;
	return data;
}
int DoubleLinkedList:: removeBack()
{
	if(isEmpty())
	{
		return -1;
	}
	else if(size == 1)
	{
		back = front;
	}
	else
	{
		back->prev->next = NULL;
	}

	IntNode *current = back;
	back = back->prev;
	back->prev = NULL;
	
	int data =  current->data;
	delete current;
	--size;
	return data;
}
bool DoubleLinkedList:: isEmpty()
{
	if(size == 0)
		return true;
	return false;
}
int DoubleLinkedList:: getFront()
{
	if(front != NULL)
		return front->data;
	return -1;
}
int DoubleLinkedList:: getBack()
{
	if(back != NULL)
	 return back->data;
	return -1;
}



