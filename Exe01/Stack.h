#ifndef __STACK_H
#define __STACK_H
#include <iostream>
#include "Node.h"
#include "ItemType.h"

class Stack
{
private:
    Node* top;

public:
    Stack();
    ~Stack();

    bool IsEmpty() const;
    void MakeEmpty();
    void Push(Node toInsert);
    Node Pop();
    Node* Top();
};

#endif // !__STACK_H
