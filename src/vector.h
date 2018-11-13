#ifndef VECTOR_H
#define VECTOR_H

#include "LinkedList.h"

namespace cs1c {
    
template<class T>
class vector
{
public:
    class iterator {
        friend class vector;
    public:
        
        T& operator*() {
           return m_vectorNode->arrayOfObjects[m_index];
        }

        iterator operator++() {
            if (++m_index >= m_vectorNode->size) {
                if (m_vectorNode != m_nodeList.tail()) {
                    m_vectorNode = m_vectorNode->next;
                }
                else {
                    m_vectorNode = nullptr;
                }
                m_index = 0;
            }
            return *this;
        }

        iterator operator++(int junk) {
            if (++m_index >= m_vectorNode->size) {
                if (m_vectorNode != m_nodeList.tail()) {
                    m_vectorNode = m_vectorNode->next;
                }
                else {
                    m_vectorNode = nullptr;
                }
                m_index = 0;
            }
            return *this;
        }
        
        bool operator==(const iterator& rhs) { 
            return ((m_vectorNode == rhs.m_vectorNode)
                    && (m_index == rhs.m_index));
        }
        
        bool operator!=(const iterator& rhs) { 
            return ((m_vectorNode != rhs.m_vectorNode)
                    || (m_index != rhs.m_index));
        }

        iterator(LinkedList<T>& nodeList,VectorNode<T>* vectorNode, int index)
          : m_nodeList{nodeList}, m_vectorNode{vectorNode}, m_index{index} {
        }
          
    private:
        LinkedList<T>&  m_nodeList;
        VectorNode<T>*  m_vectorNode;
        int             m_index;
    };

    vector();
    explicit vector(int size);
    vector(const vector<T>& source); 
    vector& operator=(const vector<T>& source);
    vector(const vector<T>&& source); 
    vector<T>& operator=(const vector<T>&& source); 
    ~vector();
    int size() const;
    int capacity() const;
    T& operator[] (int index);
    const T& operator[] (int index) const;
    void resize(int newSize);
    void reserve(int newCapacity);
    void push_back(T object);

    iterator begin() {
        if (!m_nodeList.empty()) {
            VectorNode<T>* firstNode = m_nodeList.head();
            return iterator(m_nodeList, firstNode, 0);
        }
        else {
            return iterator(m_nodeList, nullptr, 0);
        }
    }

    iterator end() {
        return iterator(m_nodeList, nullptr, 0);        
    }

    iterator insert(iterator position, const T& value) {
        VectorNode<T>* vectorNode = position.m_vectorNode;
        int insertIndex = position.m_index - 1;
        int oldSize = vectorNode->size;
        int newSize = oldSize + 1;
        T* oldArrayOfObjects = vectorNode->arrayOfObjects;
        T* newArrayOfObjects = new T[newSize];
        
        for (int index = 0; index < newSize; index++) {
            if (index < insertIndex) {
                newArrayOfObjects[index] = oldArrayOfObjects[index]; 
            }
            else if (index > insertIndex) {
                newArrayOfObjects[index + 1] = oldArrayOfObjects[index]; 
            }
            else {
                newArrayOfObjects[index] = value;
            }
        }

        vectorNode->arrayOfObjects = newArrayOfObjects;
        vectorNode->size = newSize;
        delete[] oldArrayOfObjects;
        
        return iterator(m_nodeList, vectorNode, insertIndex);
    }

    iterator erase(iterator position) {
        VectorNode<T>* vectorNode = position.m_vectorNode;
        int removeIndex = position.m_index;
        int oldSize = vectorNode->size;
        int newSize = oldSize - 1;
        T* oldArrayOfObjects = vectorNode->arrayOfObjects;
        T* newArrayOfObjects = new T[newSize];
        
        for (int index = 0; index < newSize; index++) {
            if (index < removeIndex) {
                newArrayOfObjects[index] = oldArrayOfObjects[index]; 
            }
            else if (index > removeIndex) {
                newArrayOfObjects[index - 1] = oldArrayOfObjects[index]; 
            }
        }

        vectorNode->arrayOfObjects = newArrayOfObjects;
        vectorNode->size = newSize;
        
        delete[] oldArrayOfObjects;
        if (removeIndex >= newSize) {
            removeIndex--;
        }
        
        return iterator(m_nodeList, vectorNode, removeIndex);
    }
    
private:
    // Private Member Functions
    T& get(int index) const;
    T& getNextEmpty() const;
    void clearList();
    
    // Private Data Members
    LinkedList<T> m_nodeList;
    int                     m_size;
    int                     m_capacity;
};
template<class T>
vector<T>::vector(const vector<T>&& source)
  : m_nodeList{}, m_size{source.m_size}, m_capacity{source.m_capacity} {
    while (!source.m_nodeList.empty()) {
        m_nodeList.insertAtTail(source.m_nodeList.removeFromHead());
    } 
}

template<class T>
vector<T>& vector<T>::operator=(const vector<T>&& source) {
    clearList();
    m_size = source.m_size;
    m_capacity = source.m_capacity;
    while (!source.m_nodeList.empty()) {
        m_nodeList.insertAtTail(source.m_nodeList.removeFromHead());
    }     
}

template<class T>
vector<T>& vector<T>::operator=(const vector<T>& source) {
    clearList();
    m_size = source.m_size;
    m_capacity = source.m_capacity;

    T* arrayOfObjects = new T[m_capacity];
    VectorNode<T>* node = new VectorNode<T>(arrayOfObjects, m_capacity);

    for (int index = 0; index < m_size; index++) {
        node->arrayOfObjects[index] = source[index];
    }
    m_nodeList.insertAtTail(node);
}



template<class T>
vector<T>::vector(const vector<T>& source) 
  : m_nodeList{}, m_size{source.m_size}, m_capacity{source.m_capacity}{

    T* arrayOfObjects = new T[m_capacity];
    VectorNode<T>* node = new VectorNode<T>(arrayOfObjects, m_capacity);

    for (int index = 0; index < m_size; index++) {
        node->arrayOfObjects[index] = source[index];
    }
    m_nodeList.insertAtTail(node);
}

template<class T>
vector<T>::vector() 
  : m_nodeList{}, m_size{0}, m_capacity{0} {
    
}

template<class T>
vector<T>::vector(int size)
  : m_nodeList{}, m_size{size}, m_capacity{size}  {
    T* arrayOfObjects = new T[size];
    VectorNode<T>* node = new VectorNode<T>(arrayOfObjects, size);
    m_nodeList.insertAtTail(node);
}
  
template<class T>
vector<T>::~vector() {
    clearList();
}

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
  
template<class T>
T& vector<T>::getNextEmpty() const {
    VectorNode<T>* node = m_nodeList.tail();
    int remainingCapacity = m_capacity - m_size;
    int index = node->size - remainingCapacity;
    return node->arrayOfObjects[index];
}

template<class T>
void vector<T>::clearList() {
    while (!m_nodeList.empty()) {
        VectorNode<T>* node = m_nodeList.removeFromHead();
        delete[] node->arrayOfObjects;
        delete node;
    } 
}

template<class T>
T& vector<T>::operator[] (int index) {
    return get(index);
} 

template<class T>
const T& vector<T>::operator[] (int index) const {
    return const_cast<T&>(get(index));
}

template<class T>
int vector<T>::size() const {
    return m_size;
}

template<class T>
int vector<T>::capacity() const {
    return m_capacity;
}

template<class T>
void vector<T>::reserve(int newCapacity) {
    if(newCapacity > m_capacity) {
        int additionalCapacityNeeded = newCapacity - m_capacity;
        T* arrayOfObjects = new T[additionalCapacityNeeded];
        VectorNode<T>* node = new VectorNode<T>(arrayOfObjects, additionalCapacityNeeded);
        m_nodeList.insertAtTail(node);
        m_capacity = newCapacity;
    }
}

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

} // namespace cs1c
    
#endif  // VECTOR_H

