#ifndef VECTOR_H
#define VECTOR_H

#include "LinkedList.h"

#include <algorithm>

namespace cs1c {
    //!  A vector class. 
    /*!
       A templated vector which approximates the stl vector.
    */
    template<class T>
    class vector
    {
    public:
        //!  An iterator class. 
        /*!
          An iterator which approximates the stl iterator.
        */
        class iterator {
            friend class vector;
        public:
            // Public Member Functions
            iterator(vector* sourceVector, VectorNode<T>* vectorNode, int index);
            T& operator*();
            iterator operator++();
            iterator operator++(int junk);
            bool operator==(const iterator& rhs);
            bool operator!=(const iterator& rhs);

            iterator& operator=(const iterator& rhs) {
                if (this != &rhs) {
                    m_sourceVector = rhs.m_sourceVector;
                    m_nodeList = rhs.m_nodeList;
                    m_vectorNode = rhs.m_vectorNode;
                    m_index = rhs.m_index;
                }
                return *this;
            }

        private:
            iterator moveForward();
            
            //! A private variable.
            /*!
              Source vector.
            */
            vector*         m_sourceVector;
            
            //! A private variable.
            /*!
              Linked list containing nodes.
            */
            LinkedList<T>&  m_nodeList;
            
            //! A private variable.
            /*!
              Vector node.
            */
            VectorNode<T>*  m_vectorNode;
            
            //! A private variable.
            /*!
              Index of iterator.
            */
            int             m_index;
        }; //END - class iterator

        vector();
        explicit vector(int size);
        vector(const vector<T>& source); 
        vector& operator=(const vector<T>& source);
        vector(vector<T>&& source); 
        vector<T>& operator=(vector<T>&& source); 
        ~vector();
        T& operator[] (int index);
        const T& operator[] (int index) const;
        int size() const;
        int capacity() const;
        void resize(int newSize);
        void push_back(T object);
        void reserve(int newCapacity);
		iterator erase(iterator pos);

        iterator begin();
        //const iterator begin() const;
        iterator end();
        //const iterator end() const;
        iterator insert(iterator position, const T& value);

    private:
        T& get(int index) const;
        T& getNextEmpty() const;
        void clearList();

        //! A private variable.
        /*!
          Linked list containing nodes.
        */
        LinkedList<T> m_nodeList;
        
        //! A private variable.
        /*!
          Size of the vector.
        */
        int           m_size;
        
        //! A private variable.
        /*!
          Available size of the vector.
        */
        int           m_capacity;
    }; //END - class vector
    
    //! A constructor taking three arguments.
    /*!
      Initializes the iterator with specified values.
      \param sourceVector a vector pointer.
      \param vectorNode   a VectorNode pointer.
      \param index        an integer representing the index.
    */
    template<class T>
    vector<T>::iterator::iterator(vector* sourceVector, VectorNode<T>* vectorNode, int index)
      : m_sourceVector(sourceVector), m_nodeList{sourceVector->m_nodeList}, m_vectorNode{vectorNode}, m_index{index} {
    }
    
    //! An overloaded operator taking zero arguments and returning a reference to a datatype.
    /*!
      \return The value in the vectorNode's arrayOfObjects.
    */
    template<class T>
    T& vector<T>::iterator::operator*() {
        return m_vectorNode->arrayOfObjects[m_index];
    }

    //! An overloaded operator taking zero arguments and returning an iterator.
    /*!
      \return The iterator forward a node in the vector.
    */
    template<class T>
    typename vector<T>::iterator vector<T>::iterator::operator++() {
        return moveForward();
    }

    //! An overloaded operator taking one argument and returning an iterator.
    /*!
      \param  junk An integer.
      \return The iterator forward a node in the vector.
    */
    template<class T>
    typename vector<T>::iterator vector<T>::iterator::operator++(int) {
        return moveForward();
    }

    //! An overloaded operator taking one argument and returning a bool.
    /*!
      \param  rhs Iterator on the right hand side of the operator.
      \return True if the two iterators are the same, false if they are different.
    */
    template<class T>
    bool vector<T>::iterator::operator==(const iterator& rhs) { 
        return ((m_vectorNode == rhs.m_vectorNode)
                && (m_index == rhs.m_index));
    }

    //! An overloaded operator taking one argument and returning a bool.
    /*!
      \param  rhs Iterator on the right hand side of the operator.
      \return True if the two iterators are different, false if they are the same.
    */
    template<class T>
    bool vector<T>::iterator::operator!=(const iterator& rhs) { 
        return ((m_vectorNode != rhs.m_vectorNode)
                || (m_index != rhs.m_index));
    }

    //! A private member function taking zero arguments and returning nothing.
    /*!
      Moves the iterator forward a node in the vector.
    */
    template<class T>
    typename vector<T>::iterator vector<T>::iterator::moveForward() {
        int availableNodeSize = std::min(m_vectorNode->size, m_sourceVector->m_size - (m_vectorNode->runningCapacity - m_vectorNode->size));
        if (++m_index >= availableNodeSize) {
            m_vectorNode = nullptr;
            m_index = 0;
        }
        else if (m_index >= m_vectorNode->size) {
            m_vectorNode = m_vectorNode->next;  
            m_index = 0;
        }
        return *this;
    }
   
    //! A default constructor.
    /*! 
      Initializes vector to default values.
     */
    template<class T>
    vector<T>::vector() 
      : m_nodeList{}, m_size{0}, m_capacity{0} {}
    
    //! An alternate constructor.
    /*! 
      Initializes vector to specified values.
     */
    template<class T>
    vector<T>::vector(int size)
      : m_nodeList{}, m_size{size}, m_capacity{size}  {
        T* arrayOfObjects = new T[m_capacity];
        VectorNode<T>* node = new VectorNode<T>(arrayOfObjects, m_capacity, m_capacity);
        m_nodeList.insertAtTail(node);
    }
    
    //! A copy constructor.
    /*! 
      Initializes vector with data from another vector.
     */
    template<class T>
    vector<T>::vector(const vector<T>& source) 
      : m_nodeList{}, m_size{source.m_size}, m_capacity{source.m_capacity}{
        if (m_capacity > 0) {
            T* arrayOfObjects = new T[m_capacity];
            VectorNode<T>* node = new VectorNode<T>(arrayOfObjects, m_capacity, m_capacity);

            for (int index = 0; index < m_size; index++) {
                node->arrayOfObjects[index] = source[index];
            }
            m_nodeList.insertAtTail(node);
        }
    }
    
    //! An overloaded operator taking one argument and returning a reference to a vector.
    /*!
      \param  source Vector to copy data from.
      \return A reference to itself with copied data.
    */
    template<class T>
    vector<T>& vector<T>::operator=(const vector<T>& source) {
        if (this != &source) {
            clearList();
            m_size = source.m_size;
            m_capacity = source.m_capacity;

            if (m_capacity > 0) {
                T* arrayOfObjects = new T[m_capacity];
                VectorNode<T>* node = new VectorNode<T>(arrayOfObjects, m_capacity, m_capacity);

                for (int index = 0; index < m_size; index++) {
                    node->arrayOfObjects[index] = source[index];
                }
                m_nodeList.insertAtTail(node);
            }
        }     
        return *this;
    }
      
    //! A move constructor.
    /*! 
      Initializes vector with data from another vector.
     */
    template<class T>
    vector<T>::vector(vector<T>&& source)
      : m_nodeList{}, m_size{source.m_size}, m_capacity{source.m_capacity} {
        while (!source.m_nodeList.empty()) {
            m_nodeList.insertAtTail(source.m_nodeList.removeFromHead());
        } 
    }

    //! A move assignment operator.
    /*!
      \param  source Vector to copy data from.
      \return A reference to itself with copied data.
    */
    template<class T>
    vector<T>& vector<T>::operator=(vector<T>&& source) {
        clearList();
        m_size = source.m_size;
        m_capacity = source.m_capacity;
        while (!source.m_nodeList.empty()) {
            m_nodeList.insertAtTail(source.m_nodeList.removeFromHead());
        } 
        return *this;
    }

    //! A destructor.
    /*!
      Clears the list.
    */
    template<class T>
    vector<T>::~vector() {
        clearList();
    }

    //! A public member function taking one argument and returning a reference to a datatype.
    /*!
      \param index Index to retrieve node from.
      \return A reference to the object in the node at the specified index.
    */
    template<class T>
    T& vector<T>::operator[] (int index) {
        return get(index);
    } 

    //! A public member function taking one argument and returning a constant reference to a datatype.
    /*!
      \param index Index to retrieve node from.
      \return A reference to the object in the node at the specified index.
    */
    template<class T>
    const T& vector<T>::operator[] (int index) const {
        return const_cast<T&>(get(index));
    }

    //! A public member function taking zero arguments and returning an integer value.
    /*!
      \return Current size of the vector.
    */
    template<class T>
    int vector<T>::size() const {
        return m_size;
    }

    //! A public member function taking zero arguments and returning an integer value.
    /*!
      \return Current available space of the vector.
    */
    template<class T>
    int vector<T>::capacity() const {
        return m_capacity;
    }

    //! A public member function taking one argument and returning nothing.
    /*!
      Grows the vector to the size specified.
      \param newSize New size of the vector.
    */
    template<class T>
    void vector<T>::resize(int newSize) {
        if (newSize > m_capacity) {
            reserve(newSize);
        }
        else if (newSize > m_size) {
            for (int index = m_size; index < newSize; index++) {
                T& uninitializeObject = get(index);
                uninitializeObject = T();
            }
        }
        m_size = newSize;
    }

    //! A public member function taking one argument and returning nothing.
    /*!
      Adds the specified element to the vector.
      \param object Value of the element to add to the vector.
    */
    template<class T>
    void vector<T>::push_back(T object) {
        const int MIN_ALLOC_SIZE = 8;
        if (m_capacity == 0) {
            reserve(MIN_ALLOC_SIZE);
        }
        else if (m_size == m_capacity) {
            reserve(m_capacity * 2);
        }
        T& lastObject = getNextEmpty();
        lastObject = object;
        m_size++;
    }
    
    //! A public member function taking one argument and returning nothing.
    /*!
     Increases the capacity of the vector to the specified amount.
      \param newCapacity New capacity of the vector.
    */
    template<class T>
    void vector<T>::reserve(int newCapacity) {
        if(newCapacity > m_capacity) {
            int additionalCapacityNeeded = newCapacity - m_capacity;
            T* arrayOfObjects = new T[additionalCapacityNeeded];
            VectorNode<T>* node = new VectorNode<T>(arrayOfObjects, additionalCapacityNeeded, newCapacity);
            m_nodeList.insertAtTail(node);
            m_capacity = newCapacity;
        }
    }

    //! A public member function taking zero arguments and returning an iterator.
    /*!
     \return Element to the first object in the vector.
    */
    template<class T>
    typename vector<T>::iterator vector<T>::begin() {
        if (!m_nodeList.empty()) {
            VectorNode<T>* firstNode = m_nodeList.head();
            return iterator(this, firstNode, 0);
        }
        else {
            return iterator(this, nullptr, 0);
        }
    }
    
    //! A public member function taking zero arguments and returning a constant iterator.
    /*!
     \return Element to the first object in the vector.
    */
	/*
    template<class T>
    const typename vector<T>::iterator vector<T>::begin() const {
        if (!m_nodeList.empty()) {
            VectorNode<T>* firstNode = m_nodeList.head();
            return iterator(this, firstNode, 0);
        }
        else {
            return iterator(this, nullptr, 0);
        }
    }*/

    //! A public member function taking zero arguments and returning an iterator.
    /*!
     \return Element to one past the last element of the vector.
    */
    template<class T>
    typename vector<T>::iterator vector<T>::end() {
        return iterator(this, nullptr, 0);        
    }
    
    //! A public member function taking zero arguments and returning a constant iterator.
    /*!
     \return Element to one past the last element of the vector.
    *//*
    template<class T>
    const typename vector<T>::iterator vector<T>::end() const {
        return iterator(this, nullptr, 0);        
    }*/

    //! A public member function taking two arguments and returning an iterator.
    /*!
     Inserts specified element at one past the specified position of the vector.
     \param position Iterator before position to insert new value.
     \param value    Element value to be inserted.
     \return Iterator pointing the inserted value.
    */
    template<class T>
    typename vector<T>::iterator vector<T>::insert(iterator position, const T& value) {
        VectorNode<T>* vectorNode = position.m_vectorNode;
        int insertIndex = position.m_index + 1;
        int oldSize = vectorNode->size;
        int newSize = oldSize + 1;
        T* oldArrayOfObjects = vectorNode->arrayOfObjects;
        T* newArrayOfObjects = new T[newSize];

        for (int index = 0; index < newSize; index++) {
            if (index < insertIndex) {
                newArrayOfObjects[index] = oldArrayOfObjects[index]; 
            }
            else if (index > insertIndex) {
                newArrayOfObjects[index] = oldArrayOfObjects[index - 1]; 
            }
            else {
                newArrayOfObjects[index] = value;
            }
        }

        vectorNode->arrayOfObjects = newArrayOfObjects;
        vectorNode->size = newSize;
        delete[] oldArrayOfObjects;
        
        while (vectorNode != m_nodeList.end()) {
            vectorNode->runningCapacity++;
            vectorNode = vectorNode->next;
        }        

        m_size++;
        m_capacity++;

        return iterator(this, vectorNode, insertIndex);
    }

    //! A public member function taking one argument and returning an iterator.
    /*!
     Deleted  element at the specified position of the vector.
     \param position Iterator pointing to element to erase.
     \return Iterator pointing to the element after the erased value.
    */
    template<class T>
    typename vector<T>::iterator vector<T>::erase(iterator position) {
        VectorNode<T>* vectorNode = position.m_vectorNode;
        int removeIndex = position.m_index;
        int oldSize = vectorNode->size;
        int newSize = oldSize - 1;
        T* oldArrayOfObjects = vectorNode->arrayOfObjects;
        T* newArrayOfObjects = new T[newSize];

        for (int index = 0; index < oldSize; index++) {
            if (index < removeIndex) {
                newArrayOfObjects[index] = oldArrayOfObjects[index]; 
            }
            else if (index > removeIndex) {
                newArrayOfObjects[index - 1] = oldArrayOfObjects[index]; 
            }
        }

        vectorNode->arrayOfObjects = newArrayOfObjects;
        vectorNode->size = newSize;
        
        while (vectorNode != m_nodeList.end()) {
            vectorNode->runningCapacity--;
            vectorNode = vectorNode->next;
        }        

        delete[] oldArrayOfObjects;
        if (removeIndex >= newSize) {
            removeIndex--;
        }
        m_size--;
        m_capacity--;

        return iterator(this, vectorNode, removeIndex);
    }

    //! A private member function taking one argument and returning a reference to a datatype.
    /*!
     \param index Index to retrieve node from.
     \return A reference to the object in the node at the specified index.
    */
    template<class T>
    T& vector<T>::get(int index) const {
        VectorNode<T>* node = m_nodeList.head();
        while (node != m_nodeList.end()) {
            if (index < node->size) {
                return node->arrayOfObjects[index];
            }
            index -= node->size;
            node = node->next;
        }
        static T dummy;
        return dummy;
    } 

    //! A private member function taking zero arguments and returning a reference to a datatype.
    /*!
     \return The next empty element.
    */
    template<class T>
    T& vector<T>::getNextEmpty() const {
        VectorNode<T>* node = m_nodeList.tail();
        int remainingCapacity = m_capacity - m_size;
        int index = node->size - remainingCapacity;
        return node->arrayOfObjects[index];
    }

    //! A private member function taking zero arguments and returning nothing.
    /*!
      Clears the vector.
    */
    template<class T>
    void vector<T>::clearList() {
        while (!m_nodeList.empty()) {
            VectorNode<T>* node = m_nodeList.removeFromHead();
            delete[] node->arrayOfObjects;
            delete node;
        } 
    }
} // END - namespace cs1c

#endif  // VECTOR_H
