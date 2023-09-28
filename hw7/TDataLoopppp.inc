#ifndef __TDATALOOP_H__
#define __TDATALOOP_H__

#include <iostream>
template <typename T >
class TDataLoop{
    public:
private:
/// friend DataLoopTest struct to allow the test struct access to the private data
friend struct DataLoopTest;

/**
* \struct _Node
* \brief A private structure to represent a node in a DataLoop
*/
struct _Node {
    int data;     ///< Integer node data
    _Node *next;  ///< A pointer to the next node
    _Node *prev;  ///< A pointer to the previous node
};

_Node* start;   ///< a pointer to the starting node position in the DataLoop
size_t count;   ///< the count of how many nodes/values are in the structure
}

#include "TDataLoop.inc"
#endif // __TDATALOOP_H__
