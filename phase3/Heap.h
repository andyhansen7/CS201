
#ifndef _HEAP_H_
#define _HEAP_H_

#define KEYTYPE int

#include <iostream>

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
        
        
}
#endif // !_HEAP_H_
