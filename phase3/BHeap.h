/* ==========================
 * Binomial Heap Implementation
 * CS201-001 Spring 2021
 * Developed by Andrew Hansen
 * arhansen@crimson.ua.edu
 * ===========================
 */

#include <iostream>

#define KEYTYPE int

class HeapNode
{
    public:
        HeapNode(KEYTYPE key)
            : key(key),
              degree(0),
              parent(NULL),
              child(NULL),
              rightSibling(NULL)
        {

        }

        KEYTYPE key;
        int degree = 0;

        HeapNode* parent = NULL;
        HeapNode* child = NULL;
        HeapNode* rightSibling = NULL;
};

class BHeap
{
    public:
        // Default constructor with empty heap
        BHeap();

        // Array constuctor using repeated insertion
        BHeap(KEYTYPE k[], int s);

        // Copy constructor
        BHeap(BHeap& base);

        // Copy assignment operator
        BHeap& operator=(BHeap& base);

        // Destructor
        ~BHeap();

        // Return minimum of heap without modifying the heap
        KEYTYPE peekKey();

        // Remove the minimum key of the heap and return its value
        KEYTYPE extractMin();

        // Insert key k into the tree
        void insert(KEYTYPE k);

        // Merge heap H2 into the current heap, destructively
        void merge(BHeap& H2);

        // Print the keys stored in the heap, starting with the smallest binomial tree first
        void printKey();
    
    private:
        HeapNode* _root;
        int _size;

        KEYTYPE _sentinel;

        HeapNode* mergeHelper(HeapNode* H1, HeapNode* H2);
        HeapNode* unionHelper(HeapNode* H1, HeapNode* H2);
        void linkHelper(HeapNode* y, HeapNode* z);

        HeapNode* Revert(HeapNode* y);

        void recursivePrint(HeapNode* node);
};