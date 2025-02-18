#include "SortedLinkedList.h"
#include "LinkedListNode.h"
#include "User.h"
using namespace std;
#include <iostream>
#include <cstddef>

using namespace std;

SortedLinkedList::SortedLinkedList()
{
    head = new LinkedListNode();
}

SortedLinkedList::~SortedLinkedList()
{
    LinkedListNode *tmp = head;
    while (tmp != NULL)
    {
        LinkedListNode *next = tmp->next;
        delete tmp;
        tmp = next;
    }
}

bool SortedLinkedList::add(User *u)
{
    LinkedListNode *newNode = new LinkedListNode(u);

    LinkedListNode *tmp = head;

    while (tmp->next != NULL && tmp->next->u->getId() < u->getId())
    {
        tmp = tmp->next;
    }

    newNode->next = tmp->next;
    tmp->next = newNode;

    return true;
}

bool SortedLinkedList::remove(int userId)
{
    LinkedListNode *tmp = head;

    while (tmp->next != NULL)
    {
        if (tmp->next->u->getId() == userId)
        {
            tmp->next = tmp->next->next;
            tmp = tmp->next;
            return true;
        }
        else
        {
            tmp = tmp->next;
        }
    }

    return false;
}

bool SortedLinkedList::checkIfExist(int userId)
{
    LinkedListNode *tmp = head->next;
    while (tmp != NULL)
    {
        if (tmp->u->getId() == userId)
        {
            return true;
        }
        else
        {
            tmp = tmp->next;
        }
    }

    return false;
}

LinkedListNode *SortedLinkedList::getPointerTo(int userId)
{
    LinkedListNode *tmp = head;

    while (tmp->next != NULL && tmp->next->u->getId() != userId)
    {
        tmp = tmp->next;
    }

    return tmp->next;
}

void SortedLinkedList::print()
{
    LinkedListNode *tmp = head;

    if (tmp->next == NULL)
    {
        cout << "None" << endl;
    }

    while (tmp->next != NULL)
    {
        cout << tmp->next->u->getId() << ", " << tmp->next->u->getName() << endl;
        tmp = tmp->next;
    }
}

LinkedListNode *SortedLinkedList::getHead()
{
    return head->next;
}