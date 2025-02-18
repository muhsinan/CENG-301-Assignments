// You can modify this file if needed, do not change the name of the class
#ifndef LINKED_LIST_NODE_H
#define LINKED_LIST_NODE_H
#include <cstddef>
class User;
class SortedLinkedList;
class LinkedListNode
{
public:
    User *u;
    LinkedListNode *next;
    // define new functions if needed
    // remove existing functions if needed
    LinkedListNode(User *u)
    {
        this->u = u;
        next = NULL;
    };

    LinkedListNode() : u(nullptr), next(nullptr){};

    ~LinkedListNode()
    {
        delete u;
    }
    friend class SortedLinkedList;
};
#endif