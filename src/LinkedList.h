#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "VectorNode.h"

namespace cs1c {
    //!  A LinkedList class. 
    /*!
       A templated LinkedList class which implements a circular doubly linked list.
    */
    template <class Type>
    class LinkedList {
    public:
        LinkedList();
        ~LinkedList();
        void insertAtTail(VectorNode<Type>* node);
        VectorNode<Type>* removeFromHead();
        bool empty() const;
        VectorNode<Type>* head() const;
        VectorNode<Type>* tail() const;
        VectorNode<Type>* end() const;
        VectorNode<Type>* start() const;
    private:
        //! A private variable.
        /*!
          A VectorNode pointer that points to the list head.
        */
        VectorNode<Type>* m_listHead;    
    }; // END - class LinkedList 
    
        //! A default constructor.
        /*! 
          Initializes LinkedList to default values.
         */
        template <class Type>
        LinkedList<Type>::LinkedList() 
          : m_listHead(new VectorNode<Type>()) {
        }
        
        //! A destructor.
        template <class Type>
        LinkedList<Type>::LinkedList() 
          : m_listHead(new VectorNode<Type>()) {
            delete m_listHead;
        }

        //! A public member function taking one argument and returning nothing.
        /*! 
           Inserts specified at node at the end of the linked list.
           \param node Node to insert.
         */
        template <class Type>
        void LinkedList<Type>::insertAtTail(VectorNode<Type>* node) {
            VectorNode<Type>* oldLastNode = m_listHead->previous;

            oldLastNode->next = node;
            node->next = m_listHead;
            node->previous = oldLastNode;
            m_listHead->previous = node;
        }

        //! A public member function taking zero arguments and returning a VectorNode pointer.
        /*! 
           Removes node at the front of the linked list.
           \return Removed node.
        */
        template <class Type>
        VectorNode<Type>* LinkedList<Type>::removeFromHead() {
            VectorNode<Type>* nodeToRemove = m_listHead->next;
            VectorNode<Type>* newNextNode = nodeToRemove->next;

            m_listHead->next = newNextNode;
            newNextNode->previous = m_listHead;

            nodeToRemove->next = nodeToRemove;
            nodeToRemove->previous = nodeToRemove;

            return nodeToRemove;
        }

        //! A public member function taking zero arguments and returning a bool.
        /*! 
           \return True if the linked list is empty, false if it is not empty.
        */
        template <class Type>
        bool LinkedList<Type>::empty() const {
            return (m_listHead->next == m_listHead);
        }

        //! A public member function taking zero arguments and returning a VectorNode pointer.
        /*! 
           \return First node in the list.
        */
        template <class Type>
        VectorNode<Type>* LinkedList<Type>::head() const {
            return m_listHead->next;
        }
        
        //! A public member function taking zero arguments and returning a VectorNode pointer.
        /*! 
           \return Last node in the list.
        */
        template <class Type>
        VectorNode<Type>* LinkedList<Type>::tail() const {
            return m_listHead->previous;
        }

        //! A public member function taking zero arguments and returning a VectorNode pointer.
        /*! 
           \return End of the list.
        */
        template <class Type>
        VectorNode<Type>* LinkedList<Type>::end() const {
            return m_listHead;
        }

        //! A public member function taking zero arguments and returning a VectorNode pointer.
        /*! 
           \return Beginning of the list.
        */
        template <class Type>
        VectorNode<Type>* LinkedList<Type>::start() const {
            return m_listHead;
        }
} // END - namespace cs1c

#endif 

