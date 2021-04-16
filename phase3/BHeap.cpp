/* ==========================
 * Binomial Heap Implementation
 * CS201-001 Spring 2021
 * Developed by Andrew Hansen
 * arhansen@crimson.ua.edu
 * ===========================
 */

#ifndef __BHEAP_CPP__
#define __BHEAP_CPP__

#include "BHeap.h"

// Default constructor with empty heap
template<typename K>
BHeap<K>::BHeap()
    : _minIndex(0)
{
    _rootList = new std::vector<BinomialTree<K>*>();
}

// Array constructor using repeated insertion
template<typename K>
BHeap<K>::BHeap(K k[], int s)
    : _minIndex(0)
{
    _rootList = new std::vector<BinomialTree<K>*>();

    for(int i = 0; i < s; i++) insert(k[i]);
}

// Copy constructor
template<typename K>
BHeap<K>::BHeap(BHeap<K>& base)
    : _minIndex(0)
{
    _rootList = new std::vector<BinomialTree<K>*>();

    for(unsigned int i = 0; i < base._rootList->size(); i++)
    {
        _rootList->push_back(base._rootList->at(i));
    }

    // Merge subtrees and update the min value
    MergeRootList();
    UpdateMinimum();
}

// Copy assignment operator
template<typename K>
BHeap<K>& BHeap<K>::operator=(BHeap<K>& base)
{
    _rootList->clear();

    for(unsigned int i = 0; i < base._rootList->size(); i++)
    {
        _rootList->push_back(base._rootList->at(i));
    }

    // Merge subtrees and update the min value
    MergeRootList();
    UpdateMinimum();

    return *this;
}

// Destructor
template<typename K>
BHeap<K>::~BHeap()
{
    delete _rootList;
}

// Return minimum of heap without modifying the heap
template<typename K>
K BHeap<K>::peekKey()
{
    UpdateMinimum();

    return _rootList->at(_minIndex)->array->operator[](0);
}

// Remove the minimum key of the heap and return its value
template<typename K>
K BHeap<K>::extractMin()
{
    BinomialTree<K>* _root = _rootList->at(_minIndex);
    K min = _root->array->operator[](0);

    int rootClass = _root->heapClass;
    int arrayLength = _root->array->Length();

    for(int i = rootClass - 1; i >= 0; i--)
    {
        // Create new root
        BinomialTree<K>* cutTree = new BinomialTree<K>(i);

        // Seperate values of cut tree from root
        int halfLength = arrayLength / 2;
        for(int j = 0; j < halfLength; j++) cutTree->array->AddEnd(_root->array->operator[](halfLength + j));

        // Add cut tree to root list
        _rootList->push_back(cutTree);

        // Recurse
        arrayLength /= 2;
    }

    // Remove _root from root list
    _rootList->erase(_rootList->begin() + _minIndex);

    // Clean up root list after cut nodes are put into root list
    MergeRootList();
    UpdateMinimum();

    // Return cut root value
    return min;
}

// Insert key k into the tree
template<typename K>
void BHeap<K>::insert(K k)
{
    // Create new node and new subtree
    BinomialTree<K>* newtree = new BinomialTree<K>(0);
    newtree->array->AddFront(k);

    //Empty tree - new heap is only binomial tree
    if(_rootList->size() == 0)
    {
        _rootList->push_back(newtree);
        _minIndex = 0;
    }

    // Add new heap to existing root list
    else
    {
        // Add new heap to root list
        _rootList->push_back(newtree);

        // Merge subtrees and update the min value
        MergeRootList();
        UpdateMinimum();
    }
}

// Merge heap H2 into the current heap, destructively
template<typename K>
void BHeap<K>::merge(BHeap& H2)
{
    for(unsigned int i = 0; i < H2._rootList->size(); i++)
    {
        _rootList->push_back(H2._rootList->at(i));
    }

    // Merge subtrees and update the min value
    MergeRootList();
    UpdateMinimum();
}

// Print the keys stored in the heap, starting with the smallest binomial tree first
template<typename K>
void BHeap<K>::printKey()
{
    
    // Sort root list in ascending order
    UpdateMinimum();

    for(unsigned int i = 0; i < _rootList->size(); i++)
    {
        std::cout << "B" << _rootList->at(i)->heapClass << std::endl;
        _rootList->at(i)->PrintTree();
        std::cout << std::endl << std::endl;
    }
}

// Helper function to merge nodes with duplicate classes into larger nodes
template<typename K>
void BHeap<K>::MergeRootList()
{
    int binaryRepresentation = 0;
    unsigned int numRoots = _rootList->size();

    for(unsigned int i = 0; i < numRoots; i++)
    {
        // Get current tree in list
        BinomialTree<K>* currentTree = _rootList->at(i);

        // Check for duplicate tree - if duplicate, merge trees
        if(binaryRepresentation & (1 << currentTree->heapClass))
        {
            // Find other instance of tree with same size
            for(unsigned int j = 0; j < i; j++)
            {
                // Match found
                if(_rootList->at(j)->heapClass == currentTree->heapClass)
                {
                    BinomialTree<K>* mergedTrees = currentTree->MergeTrees(currentTree, _rootList->at(j));

                    _rootList->erase(_rootList->begin() + i);
                    _rootList->erase(_rootList->begin() + j);

                    _rootList->push_back(mergedTrees);

                    // Recurse and return
                    MergeRootList();
                    return;
                }
            }
        }

        // Not already in representation - add to representation and continue
        else
        {
            binaryRepresentation = (binaryRepresentation | (1 << currentTree->heapClass));
        }
    }
}

// Helper function to sort the root list in ascending order and find the index of the minimum node
template<typename K>
void BHeap<K>::UpdateMinimum()
{
    if(_rootList->size() > 0) std::sort(_rootList->begin(), _rootList->end(), BinomialTree<K>::CompareByClass);

    for(unsigned int i = 0; i < _rootList->size(); i++)
    {
        if(i == 0 || _rootList->at(i)->array->operator[](0) < _rootList->at(_minIndex)->array->operator[](0)) _minIndex = i;
    }
}

#endif // !__BHEAP_CPP__