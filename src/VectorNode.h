#ifndef VECTOR_NODE_H
#define VECTOR_NODE_H

namespace cs1c {
    
template <class Type>
class VectorNode {
public:
    VectorNode()
      : next{this}, previous{this}, arrayOfObjects{nullptr}, size{0} {}
      
    VectorNode(Type* p_buffer, int p_size)
      : next{this}, previous{this}, arrayOfObjects{p_buffer}, size{p_size} {}
      
    VectorNode* next;
    VectorNode* previous;
    Type*       arrayOfObjects;
    int         size;
};

} // namespace cs1c

#endif 

