/* ==========================
 * Binary Heap Implementation
 * CS201-001 Spring 2021
 * Developed by Andrew Hansen
 * arhansen@crimson.ua.edu
 * ===========================
 */

#include "Heap.h"

// Default constructor
Heap::Heap()
    : _size(0)
{
    _array = new CDA<KEYTYPE>();
}

// Array constructor
Heap::Heap(KEYTYPE k[], int s)
    : _size(0)
{
    _array = new CDA<KEYTYPE>();

    for(int i = 0; i < s; i++)
    {
        insert(k[i]);
    }
}

// Destructor
Heap::~Heap()
{
    delete _array;
}

// Return minimum value of heap without modification to heap
KEYTYPE Heap::peekKey()
{
    // Minimum stored at beginning of array
    return (_array->operator[](0));
}

// Remove minimum and return value
KEYTYPE Heap::extractMin()
{
    // Safety checks
    if(_size < 1) return _sentinel;

    // Only one node
    else if(_size == 1) {
        KEYTYPE min = (_array->operator[](0));
        _array->DelFront();
        _size--;
        return min;
    }

    // All other cases
    else {
        KEYTYPE min = (_array->operator[](0));
        _array->operator[](0) = _array->operator[](_size - 1);
        _size--;

        ReHeapify(0);

        return min;
    }
}

// Insert key into heap
void Heap::insert(KEYTYPE k)
{
    _array->operator[](_size) = k;

    // Swim up
    SwimUp(_size);

    _size++;
}

// Write keys starting at root
void Heap::printKey()
{
    for(int i = 0; i < _size; i++)
    {
        std::cout << _array->operator[](i) << " ";
    }

    std::cout << std::endl;
}
// Helper to swim up or down
void Heap::SwimUp(int startIndex)
{
    int i = startIndex;

    while(i > 0 && ( _array->operator[](GetParentIndex(i)) > _array->operator[](i) ) )
    {
        // Swap values
        KEYTYPE temp = _array->operator[](i);
        _array->operator[](i) = _array->operator[](GetParentIndex(i));
        _array->operator[](GetParentIndex(i)) = temp;

        i = GetParentIndex(i);
    }
}

void Heap::ReHeapify(int index)
{
    int leftChild = GetLeftChildIndex(index);
    int rightChild = GetRightChildIndex(index);
    int min = index;

    if(leftChild < _size && _array->operator[](leftChild) < _array->operator[](index)) min = leftChild;
    if(rightChild < _size && _array->operator[](index) < _array->operator[](min)) min = rightChild;

    if(min != index) {
        KEYTYPE temp = _array->operator[](index);
        _array->operator[](index) = _array->operator[](min);
        _array->operator[](min) = temp;

        ReHeapify(min);
    }
}