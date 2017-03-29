#include <iostream>
using namespace std;
template <class type>
class IntNode
{
public:
	IntNode(type d);
	~IntNode();

	type data;
	IntNode *next;
	IntNode *prev;

};

template <class type>
IntNode<type>::IntNode(type d)
{
	data = d;
	next = NULL;
	prev = NULL;
}
template <class type>
IntNode<type>::~IntNode(){}