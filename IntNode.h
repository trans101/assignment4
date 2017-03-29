
#include <iostream>
using namespace std;
template <typename type>
class IntNode
{
public:
	type data;

	IntNode(type d);
	~IntNode();

	IntNode *next;
	IntNode *prev;

};
template <typename type>
IntNode<type>::IntNode(type d)
{
	data = d;
	next = NULL;
	prev = NULL;
}
template <typename type>
IntNode<type>:: ~IntNode(){}