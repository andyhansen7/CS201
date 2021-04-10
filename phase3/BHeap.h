
#include <iostream>

#define KEYTYPE int

class BHeap
{
    public:
        // Default constructor with empty heap
        BHeap();

        // Array constuctor using repeated insertion
        BHeap(KEYTYPE k[], int s);

        // Destructor
        ~BHeap();

        // Return minimum of heap without modifying the heap
        KEYTYPE peekKey();

        // Remove the minimum key of the heap and return its value
        KEYTYPE exctractMin();

        // Insert key k into the tree
        void insert(KEYTYPE k);

        // Merge heap H2 into the current heap, destructively
        void merge(BHeap& H2);

        // Print the keys stored in the heap, starting with the smallest binomial tree first
        void printKey();
    
    private:
}