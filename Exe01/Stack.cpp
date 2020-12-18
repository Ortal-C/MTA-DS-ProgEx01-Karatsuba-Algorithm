#include "Stack.h"

//-------------------------------------------------------------------------------------------//

//CONSTRUCTOR
Stack::Stack()	{ top = nullptr; }

//DESTRUCTOR
Stack::~Stack()	{ MakeEmpty(); }

//-------------------------------------------------------------------------------------------//

bool Stack::IsEmpty() const	{ return (top == nullptr); }

Node* Stack::Top()		{ return this->top; }

//-------------------------------------------------------------------------------------------//

void Stack::MakeEmpty()
{
    Node* temp;
    while (top != nullptr)
    {
	   temp = top;
	   top = top->getNext();
	   delete temp;
    }
}

void Stack::Push(Node toInsert)
{
    Node* tmp = top;
    top = new Node(toInsert);
    top->setNext(tmp);
}

Node Stack::Pop()
{
    if (IsEmpty())
	   cout << "ERROR! STACK IS EMPTY\n";
    Node* temp = top;
    ItemType tempData = temp->getItem();
    top = top->getNext();
    delete temp;
    return tempData;
}
