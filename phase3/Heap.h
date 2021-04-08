/* ==========================
 * Binary Heap Implementation
 * CS201-001 Spring 2021
 * Developed by Andrew Hansen
 * arhansen@crimson.ua.edu
 * ===========================
 */

#ifndef _HEAP_H_
#define _HEAP_H_

#define KEYTYPE int

#include <iostream>
#include "CDA.cpp"

class Heap
{
    public:
        // Default constructor
        Heap();

        // Array constructor
        Heap(KEYTYPE k[], int s);

        // Destructor
        ~Heap();

        // Return minimum value of heap without modification to heap
        KEYTYPE peekKey();

        // Remove minimum and return value
        KEYTYPE extractMin();

        // Insert key into heap
        void insert(KEYTYPE k);

        // Write keys starting at root
        void printKey();

    private:
        CDA<KEYTYPE>* _array;

        KEYTYPE _sentinel;

        int _size;

        // Helpers to get array indices of relatives
        int GetParentIndex(int index) { return (index / 2); }

        int GetSiblingIndex(int index) {
            if(index % 2 == 0) return index + 1;
            else return index - 1;
        }

        int GetLeftChildIndex(int index) { return (2 * index); }
        int GetRightChildIndex(int index) { return (2 * index) + 1; }

        // Helper to swim up or down
        void SwimUp(int startIndex);

        // Helper to restore heap order during extract min
        void ReHeapify(int index);
};
#endif // !_HEAP_H_
