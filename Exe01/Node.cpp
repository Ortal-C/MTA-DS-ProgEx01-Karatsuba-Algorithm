#include "Node.h"
using namespace std;

//-------------------------------------------------------------------------------------------//

//CONSTRUCTOR
Node::Node(ItemType& item, Node* next) : data(item), next(next){}

//COPY CONSTRUCTOR
Node::Node(const Node& other) : data(other.data), next(other.next){}

//DESTRUCTOR
Node::~Node(){}

//-------------------------------------------------------------------------------------------//

//GETTERS
ItemType& Node::getItem()	{ return data; }
Node* Node::getNext()		{ return next; }

//-------------------------------------------------------------------------------------------//

//SETTERS
void Node::setItem(const ItemType& newItem)	{ this->data = newItem; }
void Node::setNext(Node* newNext)		{ this->next = newNext; }

//-------------------------------------------------------------------------------------------//

//OTHERS
void Node::insertAfter(Node* newNode)
{
    newNode->next = next;
    next = newNode;
}

Node* Node::deleteAfter()
{
    Node* temp = next;
    if (next == nullptr)
	   return nullptr;

    next = temp->next;
    return(temp);
}
