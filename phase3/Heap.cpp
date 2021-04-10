/* ==========================
 * Binary Heap Implementation
 * CS201-001 Spring 2021
 * Developed by Andrew Hansen
 * arhansen@crimson.ua.edu
 * ===========================
 */

#include "Heap.h"

// Default constructor
template<typename K>
Heap<K>::Heap()
    : _size(0)
{
    _array = new CDA<K>();
}

// Array constructor
template<typename K>
Heap<K>::Heap(K k[], int s)
    : _size(s)
{
    _array = new CDA<K>();

    for(int i = 0; i < s; i++)
    {
        _array->AddEnd(k[i]);
    }

    TopDownBuildHeap();
}

// Destructor
template<typename K>
Heap<K>::~Heap()
{
    delete _array;
}

// Return minimum value of heap without modification to heap
template<typename K>
K Heap<K>::peekKey()
{
    // Minimum stored at beginning of array
    return (_array->operator[](0));
}

// Remove minimum and return value
template<typename K>
K Heap<K>::extractMin()
{
    // Safety checks
    if(_size < 1) return _sentinel;

    // Only one node
    else if(_size == 1) {
        K min = (_array->operator[](0));
        _array->DelFront();
        _size--;
        return min;
    }

    // All other cases
    else {
        K min = (_array->operator[](0));
        //_array->operator[](0) = _array->operator[](_size - 1);
        K newMin = (_array->operator[](_size - 1));
        _array->DelFront();
        _array->DelEnd();
        _array->AddFront(newMin);
        _size--;

        ReHeapify(0);

        return min;
    }
}

// Insert key into heap
template<typename K>
void Heap<K>::insert(K k)
{
    _array->AddEnd(k);

    // Swim up
    SwimUp(_size);

    _size++;
}

// Write keys starting at root
template<typename K>
void Heap<K>::printKey()
{
    for(int i = 0; i < _size; i++)
    {
        std::cout << _array->operator[](i) << " ";
    }

    std::cout << std::endl;
}
// Helper to swim up or down
template<typename K>
void Heap<K>::SwimUp(int startIndex)
{
    int i = startIndex;

    while(i > 0 && ( _array->operator[](GetParentIndex(i)) > _array->operator[](i) ) )
    {
        // Swap values
        K temp = _array->operator[](i);
        _array->operator[](i) = _array->operator[](GetParentIndex(i));
        _array->operator[](GetParentIndex(i)) = temp;

        i = GetParentIndex(i);
    }
}

// Helper to restore heap order during extract min
template<typename K>
void Heap<K>::ReHeapify(int index)
{
    int leftChild = GetLeftChildIndex(index);
    int rightChild = GetRightChildIndex(index);
    int min = index;

    if(leftChild < _array->Length() && _array->operator[](leftChild) < _array->operator[](index)) min = leftChild;
    if(rightChild < _array->Length() && _array->operator[](rightChild) < _array->operator[](min)) min = rightChild;

    if(min != index) {
        K temp = _array->operator[](index);
        _array->operator[](index) = _array->operator[](min);
        _array->operator[](min) = temp;

        ReHeapify(min);
    }
}

// Restore heap order during construction
template<typename K>
void Heap<K>::TopDownReHeapify(int index)
{
    // Check if leaf node
    if(GetLeftChildIndex(index) >= _size) return;

    // Create indices
    int leftChild = GetLeftChildIndex(index);
    int rightChild = GetRightChildIndex(index);
    int min;

    // Heap order violation
    if(_array->operator[](leftChild) < _array->operator[](index) || _array->operator[](rightChild) < _array->operator[](index))
    {
        // Swap with lesser child
        if(_array->operator[](leftChild) < _array->operator[](rightChild)) min = leftChild;
        else min = rightChild;

        K temp = _array->operator[](index);
        _array->operator[](index) = _array->operator[](min);
        _array->operator[](min) = temp;

        // Recursive call
        if(min == leftChild) TopDownReHeapify(leftChild);
        else TopDownReHeapify(rightChild);
    }

    // No violation
    else
    {
        // Done
        if(index == 0) return;

        // Recursive call on parent
        else TopDownReHeapify(GetParentIndex(index));
    }
}

template<typename K>
int Heap<K>::GetLowestParentDegree()
{
    int sum = 0;
    int n = 0;

    while(true)
    {
        int current = (1 << n);

        if(sum + current < _size)
        {
            sum += current;
            n++;
        }
        else break;
    }

    return n - 1;
}

template<typename K>
void Heap<K>::TopDownBuildHeap()
{
    bool changed = false;

    for(int i = _size - 1; i > 0; i--)
    {
        //std::cout <<"i="<<i<<std::endl;
        int index = i;
        int parent = GetParentIndex(i);
        int sibling = GetSiblingIndex(i);

        // Check if heap order violated
        if(_array->operator[](index) < _array->operator[](parent))
        {
            // Sibling is lower
            if(index != (_array->Length() - 1) && _array->operator[](sibling) < _array->operator[](index))
            {
                // Swap parent and sibling values
                K temp = _array->operator[](sibling);
                _array->operator[](sibling) = _array->operator[](parent);
                _array->operator[](parent) = temp;

                changed = true;

                continue;
            }

            // Swap with parent
            else
            {
                // Swap parent and index values
                K temp = _array->operator[](index);
                _array->operator[](index) = _array->operator[](parent);
                _array->operator[](parent) = temp;

                changed = true;

                continue;
            }
        }

        //printKey();
    }

    if(changed) TopDownBuildHeap();
}