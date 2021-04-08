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
    : _size(0)
{
    _array = new CDA<K>();

    for(int i = 0; i < s; i++)
    {
        insert(k[i]);
    }
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
        _array->operator[](0) = _array->operator[](_size - 1);
        _size--;

        ReHeapify(0);

        return min;
    }
}

// Insert key into heap
template<typename K>
void Heap<K>::insert(K k)
{
    _array->operator[](_size) = k;

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

template<typename K>
void Heap<K>::ReHeapify(int index)
{
    int leftChild = GetLeftChildIndex(index);
    int rightChild = GetRightChildIndex(index);
    int min = index;

    if(leftChild < _size && _array->operator[](leftChild) < _array->operator[](index)) min = leftChild;
    if(rightChild < _size && _array->operator[](index) < _array->operator[](min)) min = rightChild;

    if(min != index) {
        K temp = _array->operator[](index);
        _array->operator[](index) = _array->operator[](min);
        _array->operator[](min) = temp;

        ReHeapify(min);
    }
}