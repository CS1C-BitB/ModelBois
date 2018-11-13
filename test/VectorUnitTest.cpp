#include "gtest/gtest.h"
#include "VectorNode.h"
#include "LinkedList.h"
#include "vector.h"

using namespace cs1c;

const char SAMPLE_DEFAULT_NAME[] = "nothing";
const int SAMPLE_DEFAULT_VALUE = 123;

class Sample {
public:
    Sample()
      : name(SAMPLE_DEFAULT_NAME), value(SAMPLE_DEFAULT_VALUE) {
    }
    std::string name;
    int         value;
};

TEST(Vector_Node_Unit_Test, Default_Constructor_Test) {
    VectorNode<int> vectorNode;
    ASSERT_EQ(vectorNode.next, &vectorNode);    
    ASSERT_EQ(vectorNode.previous, &vectorNode); 
    ASSERT_EQ(vectorNode.arrayOfObjects, nullptr); 
    ASSERT_EQ(vectorNode.size, 0); 
}

TEST(Vector_Node_Unit_Test, Non_Default_Constructor_Test) {
    int arrayOfObjects[100];
    for (int size = 1; size < 1000; size++) {
        VectorNode<int> vectorNode(arrayOfObjects, size); 
        ASSERT_EQ(vectorNode.next, &vectorNode);    
        ASSERT_EQ(vectorNode.previous, &vectorNode); 
        ASSERT_EQ(vectorNode.arrayOfObjects, arrayOfObjects); 
        ASSERT_EQ(vectorNode.size, size); 
    }
}

TEST(Linked_List_Unit_Test, Linked_List_Constructor_Test) {
    LinkedList<int> vectorNodeLinkedList;
    ASSERT_TRUE(vectorNodeLinkedList.empty());
}

TEST(Vector_Unit_Test, Vector_Default_Constructor_Test) {
    int defaultSize = 0;
    cs1c::vector<int> vector;
    ASSERT_EQ(vector.size(), defaultSize); 
    ASSERT_EQ(vector.capacity(), defaultSize); 
}

TEST(Vector_Unit_Test, Vector_Size_Arg_Constructor_Test) {
    for (int size = 0; size < 1000; size++) {
        cs1c::vector<int> vector(size);
        ASSERT_EQ(vector.size(), size); 
        ASSERT_EQ(vector.capacity(), size); 
    }
}

TEST(Vector_Unit_Test, Vector_Size_Constructor_Test) {
    const int SIZE = 10;
    cs1c::vector<Sample> sampleVector(SIZE);
    ASSERT_EQ(sampleVector.size(), SIZE); 
    ASSERT_EQ(sampleVector.capacity(), SIZE); 
    for (int index = 0; index < SIZE; index++) {
        Sample sample = sampleVector[index];
        ASSERT_EQ(sample.value, SAMPLE_DEFAULT_VALUE); 
        ASSERT_STREQ(sample.name.c_str(), SAMPLE_DEFAULT_NAME); 
    }
}
TEST(Vector_Unit_Test, Copy_Constructor_Test) {
    const int SIZE = 10;
    cs1c::vector<int> listA(SIZE);
    for (int index = 0; index < listA.size(); index++) {
        listA[index] = index;
    }
    listA.push_back(SIZE);
    listA.reserve(SIZE * 10);
    
    cs1c::vector<int> listB = listA;
    ASSERT_EQ(listA.size(), listB.size());
    ASSERT_EQ(listA.capacity(), listB.capacity());
    
    for (int index = 0; index < listA.size(); index++) {
        ASSERT_EQ(listA[index], listB[index]);
    }
}

TEST(Vector_Unit_Test, Single_Node_Constructor_Test) {
    int seed = 123;
    for (int size = 1; size < 1000; size++) {
        cs1c::vector<int> list(size);
        ASSERT_EQ(list.size(), size);
        ASSERT_EQ(list.capacity(), size);
        for (int index = 0; index < size; index++) {
            list[index] = seed + index;
        }
        for (int index = 0; index < size; index++) {
            ASSERT_EQ(list[index], seed + index);
        }
    }
}

TEST(Vector_Unit_Test, Multiple_Node_Test) {
    int seed = 62;
    int nodeSize = 10;
    int totalSize = nodeSize;
    int oldSize = 0;
    cs1c::vector<int> list;
    ASSERT_EQ(list.size(), 0);
    ASSERT_EQ(list.capacity(), 0);
    for (int nodeCount = 1; nodeCount < 10; nodeCount++) {
        list.resize(totalSize);
        ASSERT_EQ(list.size(), totalSize);
        ASSERT_EQ(list.capacity(), totalSize);
        for (int index = oldSize; index < list.size(); index++) {
            list[index] = seed + index;
        }
        for (int index = 0; index < list.size(); index++) {
            ASSERT_EQ(list[index], seed + index);
        }
        nodeSize *= 2;
        oldSize = totalSize;
        totalSize += nodeSize;
    }
}

TEST(Vector_Unit_Test, Multiple_Node_Capacity_Test) {
    int nodeSize = 10;
    int totalSize = nodeSize;
    cs1c::vector<int> list;
    ASSERT_EQ(list.size(), 0);
    ASSERT_EQ(list.capacity(), 0);
    for (int nodeCount = 1; nodeCount < 10; nodeCount++) {
        list.reserve(totalSize);
        ASSERT_EQ(list.size(), 0);
        ASSERT_EQ(list.capacity(), totalSize);
        nodeSize *= 2;
        totalSize += nodeSize;
    }
}

TEST(Vector_Unit_Test, Single_Node_Push_Back_Test) {
    int seed = 98;
    cs1c::vector<int> list;
    ASSERT_EQ(list.size(), 0);
    ASSERT_EQ(list.capacity(), 0);
    for (int entryCount = 1; entryCount <= 8; entryCount++) {
        list.push_back((entryCount - 1) + seed);
        ASSERT_EQ(list.size(), entryCount);
        ASSERT_EQ(list.capacity(), 8);
        for (int index = 0; index < list.size(); index++) {
             ASSERT_EQ(list[index], seed + index);
        }
    }
}

TEST(Vector_Unit_Test, Multi_Node_Push_Back_Test) {
    int seed = 98;
    cs1c::vector<int> list;
    ASSERT_EQ(list.size(), 0);
    ASSERT_EQ(list.capacity(), 0);
    int capacity = 8;
    for (int entryCount = 1; entryCount <= 1024; entryCount++) {
        list.push_back((entryCount - 1) + seed);
        ASSERT_EQ(list.size(), entryCount);
        if (entryCount > capacity)
            capacity *= 2;
        ASSERT_EQ(list.capacity(), capacity);
        for (int index = 0; index < list.size(); index++) {
             ASSERT_EQ(list[index], seed + index);
        }
    }
}

TEST(Vector_Unit_Test, Single_Node_Iterator_Test) {
    int seed = 0;
    for (int size = 1; size < 1000; size++) {
        cs1c::vector<int> list(size);
        ASSERT_EQ(list.size(), size);
        ASSERT_EQ(list.capacity(), size);
        for (int index = 0; index < size; index++) {
            list[index] = seed + index;
        }
        for (int pre = 0; pre < 2; pre++) {
            int index = 0;
            cs1c::vector<int>::iterator iter = list.begin();
            while (iter != list.end()) {
                int expectedValue = seed + index;
                int value = *iter;
                ASSERT_EQ(value, expectedValue);
                index++;
                if (pre == 0) {
                    ++iter;
                }
                else {
                    iter++;
                }
            }
        }
    }
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
