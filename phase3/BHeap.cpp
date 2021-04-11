/* ==========================
 * Binomial Heap Implementation
 * CS201-001 Spring 2021
 * Developed by Andrew Hansen
 * arhansen@crimson.ua.edu
 * ===========================
 */

#include "BHeap.h"

// Default constructor with empty heap
BHeap::BHeap()
    : _root(NULL), _size(0)
{

}

// Array constuctor using repeated insertion
BHeap::BHeap(KEYTYPE k[], int s)
    : _root(NULL), _size(0)
{
    for(int i = 0; i < s; i++) insert(k[i]);
}

// Destructor
BHeap::~BHeap()
{

}

// Return minimum of heap without modifying the heap
KEYTYPE BHeap::peekKey()
{
    return _root->key;
}

// Remove the minimum key of the heap and return its value
KEYTYPE BHeap::extractMin()
{
    return 0;
}

// Insert key k into the tree
void BHeap::insert(KEYTYPE k)
{
    // If tree is empty, insert new node
    if(_size == 0) {
        HeapNode* newnode = new HeapNode(k);
        _root = newnode;
    }
    // Create new empty heap, insert one element and merge
    else {
        BHeap* newheap = new BHeap();
        newheap->insert(k);
        merge(*newheap);
    }

    _size++;
}

// Merge heap H2 into the current heap, destructively
void BHeap::merge(BHeap& H2)
{

}

// Print the keys stored in the heap, starting with the smallest binomial tree first
void BHeap::printKey()
{

}