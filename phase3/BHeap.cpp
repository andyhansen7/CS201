/* ==========================
 * Binomial Heap Implementation
 * CS201-001 Spring 2021
 * Developed by Andrew Hansen
 * arhansen@crimson.ua.edu
 * ===========================
 */

#include "BHeap.h"

// Default constructor with empty heap
template<typename K>
BHeap<K>::BHeap()
    : _root(NULL), _rootListSize(0)
{

}

// Array constructor using repeated insertion
template<typename K>
BHeap<K>::BHeap(K k[], int s)
    : _root(NULL), _rootListSize(0)
{
    for(int i = 0; i < s; i++) insert(k[i]);
}

// Copy constructor
template<typename K>
BHeap<K>::BHeap(BHeap<K>& base)
    : _root(NULL), _rootListSize(0)
{

}

// Copy assignment operator
template<typename K>
BHeap<K>& BHeap<K>::operator=(BHeap<K>& base)
{
    return *this;
}

// Destructor
template<typename K>
BHeap<K>::~BHeap()
{

}

// Return minimum of heap without modifying the heap
template<typename K>
K BHeap<K>::peekKey()
{
    return _root->root->key;
}

// Remove the minimum key of the heap and return its value
template<typename K>
K BHeap<K>::extractMin()
{
   return _root->root->key;
}

// Insert key k into the tree
template<typename K>
void BHeap<K>::insert(K k)
{
    std::cout << "Insert value " << k << " into tree" << std::endl;

    // Create new node and new subtree
    HeapNode<K>* newnode = new HeapNode<K>(k);
    BinomialTree<K>* newheap = new BinomialTree<K>(newnode, 0);

    //Empty tree - new heap is only binomial tree
    if(_root == NULL) _root = newheap;

    // Add new heap to existing root list
    else
    {
        // Add new heap to root list
        BinomialTree<K>* temp = _root;
        while(temp->rightSibling != NULL) temp = temp->rightSibling;

        temp->rightSibling = newheap;
        newheap->leftSibling = temp;
        _rootListSize++;

        std::cout << "Done adding new node to root list" << std::endl;

        MergeRootList();

        printKey();

        UpdateRoot();

        printKey();
    }

    _rootListSize++;
}

// Merge heap H2 into the current heap, destructively
template<typename K>
void BHeap<K>::merge(BHeap& H2)
{
    
}

// Print the keys stored in the heap, starting with the smallest binomial tree first
template<typename K>
void BHeap<K>::printKey()
{
    BinomialTree<K>* temp = _root;

    while(temp != NULL)
    {
        std::cout << "B" << temp->heapClass << std::endl;
        RecursivePrint(temp->root);
        std::cout << std::endl;
        temp = temp->rightSibling;
    }
}

template<typename K>
void BHeap<K>::MergeRootList()
{
    int binaryRepresentation = 0;

    BinomialTree<K>* temp = _root;

    while(temp != NULL)
    {
        // Entry already at position
        if(binaryRepresentation & (1 << temp->heapClass))
        {
            std::cout << "Merging trees of duplicate size: B" << temp->heapClass << std::endl; 
            printKey();

            // Merge duplicate trees
            BinomialTree<K>* otherTree = _root;

            while((otherTree->heapClass != temp->heapClass) && (otherTree != temp) && (otherTree->rightSibling != NULL)) otherTree = otherTree->rightSibling;

            std::cout << "temp tree is key " << temp->root->key << ", other is " << otherTree->root->key << std::endl;

            // Check if same tree
            if(temp == otherTree) return;

            // Found second tree, combine trees - smaller index should be root
            HeapNode<K>* newHeapRoot;

            // Error checking
            if(temp->heapClass != otherTree->heapClass)
            {
                std::cout << "[Error] Merge of non-matching heap classes" << std::endl;
                return;
            }

            // Temp has smaller key, parent of other
            if(temp->root->key < otherTree->root->key)
            {
                newHeapRoot = temp->root;

                // Set children
                HeapNode<K>* prevChild = newHeapRoot->child;
                newHeapRoot->child = otherTree->root;
                otherTree->root->parent = newHeapRoot;
                otherTree->root->rightSibling = prevChild;
                if(prevChild != NULL) prevChild->leftSibling = otherTree->root;
            }
            // Other has smaller key, parent of temp
            else 
            {
                newHeapRoot = otherTree->root;

                // Set children
                HeapNode<K>* prevChild = newHeapRoot->child;
                newHeapRoot->child = temp->root;
                temp->root->parent = newHeapRoot;
                temp->root->rightSibling = prevChild;
                if(prevChild != NULL) prevChild->leftSibling = temp->root;
            }

            // Build new tree
            BinomialTree<K>* newtree = new BinomialTree<K>(newHeapRoot, temp->heapClass + 1);

            std::cout << "Finished building new tree" << std::endl;

            // Remove old trees from root list
            if(otherTree->leftSibling != NULL) otherTree->leftSibling->rightSibling = otherTree->rightSibling;
            else if(otherTree->rightSibling != NULL) otherTree->rightSibling->leftSibling = otherTree->leftSibling;

            if(temp->leftSibling != NULL) temp->leftSibling->rightSibling = temp->rightSibling;
            else if(temp->leftSibling != NULL) temp->rightSibling->leftSibling = temp->leftSibling;

            // Update representation
            binaryRepresentation = (binaryRepresentation ^ (1 << (temp->heapClass + 1)));
            std::cout << "New bin rep is " << binaryRepresentation << std::endl;

            _rootListSize--;

            // Insert new tree into end of list
            BinomialTree<K>* last = temp;
            while(last->rightSibling != NULL) last = last->rightSibling;
            last->rightSibling = newtree;
            newtree->leftSibling = last;
        }

        // Update array
        else 
        {
            binaryRepresentation = (binaryRepresentation | (1 << temp->heapClass));

            std::cout << "Binary rep now contains tree B" << temp->heapClass << std::endl;
        }

        temp = temp->rightSibling;
    }
}

template<typename K>
void BHeap<K>::UpdateRoot()
{
    BinomialTree<K>* temp = _root;

    while(temp != NULL)
    {
        if(temp->root->key < _root->root->key) _root = temp;

        temp = temp->rightSibling;
    }
}

template<typename K>
void BHeap<K>::RecursivePrint(HeapNode<K>* temp)
{
    std::cout << temp->key << " ";
    if(temp->child != NULL) RecursivePrint(temp->child);
    if(temp->rightSibling != NULL) RecursivePrint(temp->rightSibling);
}