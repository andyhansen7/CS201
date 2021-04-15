/* ==========================
 * Binomial Heap Implementation
 * CS201-001 Spring 2021
 * Developed by Andrew Hansen
 * arhansen@crimson.ua.edu
 * ===========================
 */

#include "BHeap2.h"

// Default constructor with empty heap
template<typename K>
BHeap<K>::BHeap()
    : _root(NULL), _size(0)
{

}

// Array constuctor using repeated insertion
template<typename K>
BHeap<K>::BHeap(K k[], int s)
    : _root(NULL), _size(0)
{
    for(int i = 0; i < s; i++)
    {
        insert(k[i]);
        //printKey();
    }
}

// Copy constructor
template<typename K>
BHeap<K>::BHeap(BHeap& base)
    : _root(NULL), _size(0)
{

}

// Copy assignment operator
template<typename K>
BHeap<K>& BHeap<K>::operator=(BHeap<K>& base)
{

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
    Hr = NULL;
    HeapNode<K>* t = NULL;
    HeapNode<K>* x = _root;
    if(x == NULL)
    {
        std::cout<<"Nothing to Extract"<<std::endl;
        return _sentinel;
    }
    K min = x->key;
    HeapNode<K>* p = x;
    while(p->sibling != NULL)
    {
        if ((p->sibling)->key < min)
        {
            min = (p->sibling)->key;
            t = p;
            x = p->sibling;
        }
        p = p->sibling;
    }
    if(t == NULL && x->sibling == NULL) _root = NULL;
    else if(t == NULL) _root = x->sibling;
    else if(t->sibling == NULL) t = NULL;
    else t->sibling = x->sibling;
    if(x->child != NULL)
    {
        RevertHelper(x->child);
        (x->child)->sibling = NULL;
    }
    //_root = UnionHelper(_root, Hr);
    
    _size--;

    return min;
}

// Insert key k into the tree
template<typename K>
void BHeap<K>::insert(K k)
{
    HeapNode<K>* newnode = new HeapNode<K>(k);
    _root = UnionHelper(_root, newnode);
    _size++;
}

// Merge heap H2 into the current heap, destructively
template<typename K>
void BHeap<K>::merge(BHeap<K>& H2)
{
    /*int size = H2.size();

    for(int i = 0; i < size; i++)
    {
        HeapNode<K>* temp = new HeapNode<K>(H2.extractMin());
        //_root = UnionHelper(_root, otherRoot);
        _root = UnionHelper(_root, temp);
        //otherRoot = otherRoot->sibling;
    }*/
}

// Print the keys stored in the heap, starting with the smallest binomial tree first
template<typename K>
void BHeap<K>::printKey()
{
    HeapNode<K>* temp = _root;

    while(temp != NULL)
    {
        std::cout << "B" << temp->degree << std::endl;
        RecursivePrint(temp, (1 << (temp->degree)));
        temp = temp->sibling;
        std::cout << std::endl << std::endl;
    }
    //std::cout << std::endl;
}

// Get the current size of the tree
template<typename K>
int BHeap<K>::size()
{
    return _size;
}

template<typename K>
void BHeap<K>::RevertHelper(HeapNode<K>* y)
{
    if (y->sibling != NULL)
    {
        RevertHelper(y->sibling);
        (y->sibling)->sibling = y;
    }
    else
    {
        Hr = y;
    }
}

template<typename K>
HeapNode<K>* BHeap<K>::UnionHelper(HeapNode<K>* H1, HeapNode<K>* H2)
{
    HeapNode<K>* H = MergeHelper(H1, H2);
    if (H == NULL)
        return H;
    HeapNode<K>* prev_x;
    HeapNode<K>* next_x;
    HeapNode<K>* x;
    prev_x = NULL;
    x = H;
    next_x = x->sibling;
    while (next_x != NULL)
    {
        if ((x->degree != next_x->degree) || ((next_x->sibling != NULL)
            && (next_x->sibling)->degree == x->degree))
        {
            prev_x = x;
            x = next_x;
        }
        else
	    {
            if (x->key <= next_x->key)
            {
                x->sibling = next_x->sibling;
                LinkHelper(next_x, x);
            }
            else
            {
                if (prev_x == NULL)
                    H = next_x;
                else
                    prev_x->sibling = next_x;
                LinkHelper(x, next_x);
                x = next_x;
            }
	    }
        next_x = x->sibling;
    }
    return H;
}

template<typename K>
HeapNode<K>* BHeap<K>::MergeHelper(HeapNode<K>* H1, HeapNode<K>* H2)
{
    HeapNode<K>* H = NULL;
    HeapNode<K>* y;
    HeapNode<K>* z;
    HeapNode<K>* a;
    HeapNode<K>* b;
    y = H1;
    z = H2;
    if (y != NULL)
    {
        if (z != NULL)
        {
            if (y->degree <= z->degree)
                H = y;
            else if (y->degree > z->degree)
                H = z;
        }
        else
            H = y;
    }
    else
        H = z;
    while (y != NULL && z != NULL)
    {
        if (y->degree < z->degree)
        {
            y = y->sibling;
        }
        else if (y->degree == z->degree)
        {
            a = y->sibling;
            y->sibling = z;
            y = a;
        }
        else
        {
            b = z->sibling;
            z->sibling = y;
            z = b;
        }
    }
    return H;
}

template<typename K>
void BHeap<K>::LinkHelper(HeapNode<K>* y, HeapNode<K>* z)
{
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree = z->degree + 1;
}

template<typename K>
void BHeap<K>::RecursivePrint(HeapNode<K>* temp, int nodesLeft)
{
    int remaining = nodesLeft;

    if(remaining > 0)
    {
        std::cout << temp->key << " ";
        if(temp->child != NULL)
        {
            remaining -= 1;
            RecursivePrint(temp->child, remaining);
        }

        if(temp->sibling != NULL)
        {
            remaining -= 1;
            RecursivePrint(temp->sibling, remaining);
        }
    }
}