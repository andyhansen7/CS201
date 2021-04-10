/* ==========================
 * Binary Heap Implementation
 * CS201-001 Spring 2021
 * Developed by Andrew Hansen
 * arhansen@crimson.ua.edu
 * ===========================
 */

#ifndef _HEAP_H_
#define _HEAP_H_

#include <iostream>
#include <cmath>
#include "CDA.cpp"

template<typename K>
class Heap
{
    public:
        // Default constructor
        Heap();

        // Array constructor
        Heap(K k[], int s);

        // Destructor
        ~Heap();

        // Return minimum value of heap without modification to heap
        K peekKey();

        // Remove minimum and return value
        K extractMin();

        // Insert key into heap
        void insert(K k);

        // Write keys starting at root
        void printKey();

    private:
        CDA<K>* _array;

        K _sentinel;

        int _size;

        // Helpers to get array indices of relatives
        int GetParentIndex(int index) { 
            if(index % 2 == 0) index--;
            return ( index / 2 ); 
        }

        int GetSiblingIndex(int index) {
            if(index % 2 == 0) return index - 1;
            else return index + 1;
        }

        int GetLeftChildIndex(int index) { return (2 * index + 1); }
        int GetRightChildIndex(int index) { return (2 * index + 2); }

        // Helper to swim up or down
        void SwimUp(int startIndex);

        // Helper to restore heap order during extract min
        void ReHeapify(int index);

        // Restore heap order during construction
        void TopDownReHeapify(int index);

        int GetLowestParentDegree();

        void TopDownBuildHeap();
};
#endif // !_HEAP_H_