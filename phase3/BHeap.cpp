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
    : _root(NULL), _revertNode(NULL), _size(0)
{

}

// Array constructor using repeated insertion
template<typename K>
BHeap<K>::BHeap(K k[], int s)
    : _root(NULL), _revertNode(NULL), _size(0)
{
    for(int i = 0; i < s; i++) insert(k[i]);
}

// Copy constructor
template<typename K>
BHeap<K>::BHeap(BHeap<K>& base)
    : _root(NULL), _revertNode(NULL), _size(0)
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
    return _root->key;
}

// Remove the minimum key of the heap and return its value
template<typename K>
K BHeap<K>::extractMin()
{
    _revertNode = NULL;
    HeapNode<K>* t = NULL;
    HeapNode<K>* x = _root;

    if(x == NULL) return _sentinel;
    K min = x->key;

    HeapNode<K>* p = x;
    while (p->rightSibling != NULL)
    {
        if ((p->rightSibling)->key < min)
        {
            min = (p->rightSibling)->key;
            t = p;
            x = p->rightSibling;
        }
        p = p->rightSibling;
    }
    if (t == NULL && x->rightSibling == NULL)
        _root = NULL;
    else if (t == NULL)
        _root = x->rightSibling;
    else if (t->rightSibling == NULL)
        t = NULL;
    else
        t->rightSibling = x->rightSibling;
    if (x->child != NULL)
    {
        revert(x->child);
        (x->child)->rightSibling = NULL;
    }
    _root = unionHelper(_root, _revertNode);
    
    return min;
}

// Insert key k into the tree
template<typename K>
void BHeap<K>::insert(K k)
{
    HeapNode<K>* newnode = new HeapNode<K>(k);

    _root = unionHelper(_root, newnode);

    _size++;
}

// Merge heap H2 into the current heap, destructively
template<typename K>
void BHeap<K>::merge(BHeap& H2)
{
    _root = mergeHelper(_root, H2._root);
}

// Print the keys stored in the heap, starting with the smallest binomial tree first
template<typename K>
void BHeap<K>::printKey()
{
    std::cout << "B" << _root->degree << std::endl;
    recursivePrint(_root);
    std::cout << std::endl;
}

template<typename K>
HeapNode<K>* BHeap<K>::mergeHelper(HeapNode<K>* H1, HeapNode<K>* H2)
{
    HeapNode<K>* newHeap;
    HeapNode<K>* y = H1;
    HeapNode<K>* z = H2;

    if(y != NULL)
    {
        if(z != NULL)
        {
            if(y->degree <= z->degree) newHeap = y;
            else newHeap = z;
        }
        else newHeap = y;
    }
    else newHeap = z;

    while(y != NULL && z != NULL)
    {
        if(y->degree < z->degree) y = y->rightSibling;
        
        else if(y->degree == z->degree)
        {
            HeapNode<K>* temp = y->rightSibling;
            y->rightSibling = z;
            y = temp;
        }

        else
        {
            HeapNode<K>* temp = z->rightSibling;
            z->rightSibling = y;
            z = temp;
        }
    }

    return newHeap;
}

template<typename K>
HeapNode<K>* BHeap<K>::unionHelper(HeapNode<K>* H1, HeapNode<K>* H2)
{
    HeapNode<K>* H = mergeHelper(H1, H2);
    if(H == NULL) return H;

    HeapNode<K>* prev_x;
    HeapNode<K>* next_x;
    HeapNode<K>* x;

    prev_x = NULL;
    x = H;
    next_x = x->rightSibling;

    while(next_x != NULL)
    {
        if ((x->degree != next_x->degree) || ((next_x->rightSibling != NULL)
            && (next_x->rightSibling)->degree == x->degree))
        {
            prev_x = x;
            x = next_x;
        }
        else
	    {
            if (x->key <= next_x->key)
            {
                x->rightSibling = next_x->rightSibling;
                linkHelper(next_x, x);
            }
            else
            {
                if (prev_x == NULL)
                    H = next_x;
                else
                    prev_x->rightSibling = next_x;
                linkHelper(x, next_x);
                x = next_x;
            }
	    }
        next_x = x->rightSibling;
    }
    return H;
}

template<typename K>
void BHeap<K>::linkHelper(HeapNode<K>* y, HeapNode<K>* z)
{
    y->parent = z;
    y->rightSibling = z->child;
    z->child = y;
    z->degree++;
}

template<typename K>
void BHeap<K>::revert(HeapNode<K>* y)
{
    if (y->rightSibling != NULL)
    {
        revert(y->rightSibling);
        y->rightSibling->rightSibling = y;
    }
    else
    {
        _revertNode = y;
    }
}

template<typename K>
void BHeap<K>::recursivePrint(HeapNode<K>* node)
{
    std::cout << node->key << " ";
    if(node->child != NULL) recursivePrint(node->child);
    if(node->rightSibling != NULL) recursivePrint(node->rightSibling);
}