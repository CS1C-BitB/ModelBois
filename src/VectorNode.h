#ifndef VECTOR_NODE_H
#define VECTOR_NODE_H

namespace cs1c {
    //!  A VectorNode class. 
    /*!
       A templated VectorNode class that works with vector.
    */
    template <class Type>
    class VectorNode {
    public:
        VectorNode();

        VectorNode(Type* p_buffer, int p_size, int p_runningCapacity);

        //! A private variable.
        /*!
          A VectorNode pointer that points the next node in the vector.
        */
        VectorNode* next;
        
        //! A private variable.
        /*!
          A VectorNode pointer that points the previous node in the vector.
        */
        VectorNode* previous;
        
        //! A private variable.
        /*!
          A pointer to a datatype that points to an array of objects.
        */
        Type*       arrayOfObjects;
        
        //! A private variable.
        /*!
          Size of array in the node.
        */
        int         size;
        
        //! A private variable.
        /*!
         Running capacity of elements in node.
        */
        int         runningCapacity;
    }; // END - class VectorNode
    
    //! A default constructor.
    /*! 
      Initializes VectorNode to default values.
     */
    template <class Type>
    VectorNode<Type>::VectorNode()
      : next{this}, previous{this}, arrayOfObjects{nullptr}, size{0}, runningCapacity{0} {}
      
    //! An alternate constructor.
    /*! 
      Initializes VectorNode to specified values.
     */
    template <class Type>
    VectorNode<Type>::  VectorNode(Type* p_buffer, int p_size, int p_runningCapacity)
      : next{this}, previous{this}, arrayOfObjects{p_buffer}, size{p_size}, runningCapacity{p_runningCapacity} {}
    
} // END - namespace cs1c

#endif 

