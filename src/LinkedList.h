#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "VectorNode.h"

namespace cs1c {
    
template <class Type>
class LinkedList {
public:
    LinkedList() 
      : m_listHead(new VectorNode<Type>()) {
      }
      
    void insertAtTail(VectorNode<Type>* node) {
        VectorNode<Type>* oldLastNode = m_listHead->previous;

        oldLastNode->next = node;
        node->next = m_listHead;
        node->previous = oldLastNode;
        m_listHead->previous = node;
    }

    VectorNode<Type>* removeFromHead() {
        VectorNode<Type>* nodeToRemove = m_listHead->next;
        VectorNode<Type>* newNextNode = nodeToRemove->next;

        m_listHead->next = newNextNode;
        newNextNode->previous = m_listHead;

        nodeToRemove->next = nodeToRemove;
        nodeToRemove->previous = nodeToRemove;

        return nodeToRemove;
    }

    bool empty() const {
        return (m_listHead->next == m_listHead);
    }
    
    VectorNode<Type>* head() const {
        return m_listHead->next;
    }
    
    VectorNode<Type>* tail() const {
        return m_listHead->previous;
    }

    VectorNode<Type>* end() const {
        return m_listHead;
    }
    
    VectorNode<Type>* start() const {
        return m_listHead;
    }
    
private:
    VectorNode<Type>* m_listHead;    
};

} // namespace cs1c

#endif 

