#ifndef __NODE_H
#define __NODE_H
#include <iostream>
#include "ItemType.h"
using namespace std;

class Node
{
private:
    ItemType data;
    Node* next;
public:
    Node(ItemType& item, Node* next = nullptr);
    Node(const Node& other);
    ~Node();

    //GETTERS
    ItemType& getItem();
    Node* getNext();

    //SETTERS
    void setItem(const ItemType& newItem);
    void setNext(Node* newNext);

    void insertAfter(Node* newNode);
    Node* deleteAfter();
};

#endif // !__NODE_H
