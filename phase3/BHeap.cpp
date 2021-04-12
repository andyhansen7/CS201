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
    : _root(NULL), _revertNode(NULL), _size(0)
{

}

// Array constructor using repeated insertion
BHeap::BHeap(KEYTYPE k[], int s)
    : _root(NULL), _revertNode(NULL), _size(0)
{
    for(int i = 0; i < s; i++) insert(k[i]);
}

// Copy constructor
BHeap::BHeap(BHeap& base)
    : _root(NULL), _revertNode(NULL), _size(0)
{

}

// Copy assignment operator
BHeap& BHeap::operator=(BHeap& base)
{
    return *this;
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
    _revertNode = NULL;
    HeapNode* t = NULL;
    HeapNode* x = _root;

    if(x == NULL) return _sentinel;
    KEYTYPE min = x->key;

    HeapNode* p = x;
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
void BHeap::insert(KEYTYPE k)
{
    HeapNode* newnode = new HeapNode(k);

    _root = unionHelper(_root, newnode);

    _size++;
}

// Merge heap H2 into the current heap, destructively
void BHeap::merge(BHeap& H2)
{
    _root = mergeHelper(_root, H2._root);
}

// Print the keys stored in the heap, starting with the smallest binomial tree first
void BHeap::printKey()
{
    std::cout << "B" << _root->degree << std::endl;
    recursivePrint(_root);
    std::cout << std::endl;
}

HeapNode* BHeap::mergeHelper(HeapNode* H1, HeapNode* H2)
{
    HeapNode* newHeap;
    HeapNode* y = H1;
    HeapNode* z = H2;

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
            HeapNode* temp = y->rightSibling;
            y->rightSibling = z;
            y = temp;
        }

        else
        {
            HeapNode* temp = z->rightSibling;
            z->rightSibling = y;
            z = temp;
        }
    }

    return newHeap;
}

HeapNode* BHeap::unionHelper(HeapNode* H1, HeapNode* H2)
{
    HeapNode* H = mergeHelper(H1, H2);
    if(H == NULL) return H;

    HeapNode* prev_x;
    HeapNode* next_x;
    HeapNode* x;

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

void BHeap::linkHelper(HeapNode* y, HeapNode* z)
{
    y->parent = z;
    y->rightSibling = z->child;
    z->child = y;
    z->degree++;
}

void BHeap::revert(HeapNode* y)
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

void BHeap::recursivePrint(HeapNode* node)
{
    std::cout << node->key << " ";
    if(node->child != NULL) recursivePrint(node->child);
    if(node->rightSibling != NULL) recursivePrint(node->rightSibling);
}