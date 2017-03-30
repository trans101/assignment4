#include <iostream>
using namespace std;
template <class type>
class IntNode
{
public:
	IntNode(type d);
	~IntNode();

	type data;
	IntNode<type> *next;
	IntNode<type> *prev;

};

template <class type>
IntNode<type>::IntNode(type d)
{
	data = d;
	next = NULL; 
	prev = NULL;
	//for some reason calling the student destructor
}
template <class type>
IntNode<type>::~IntNode()
{
	next = NULL;
	prev = NULL;
}