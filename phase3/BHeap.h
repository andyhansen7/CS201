/* ==========================
 * Binomial Heap Implementation
 * CS201-001 Spring 2021
 * Developed by Andrew Hansen
 * arhansen@crimson.ua.edu
 * ===========================
 */

#include <iostream>

template<typename K>
class HeapNode
{
    public:
        HeapNode(K key)
            : key(key),
              degree(0),
              parent(NULL),
              child(NULL),
              rightSibling(NULL)
        {

        }

        K key;
        int degree = 0;

        HeapNode<K>* parent = NULL;
        HeapNode<K>* child = NULL;
        HeapNode<K>* rightSibling = NULL;
};

template<typename K>
class BHeap
{
    public:
        // Default constructor with empty heap
        BHeap();

        // Array constuctor using repeated insertion
        BHeap(K k[], int s);

        // Copy constructor
        BHeap(BHeap& base);

        // Copy assignment operator
        BHeap& operator=(BHeap& base);

        // Destructor
        ~BHeap();

        // Return minimum of heap without modifying the heap
        K peekKey();

        // Remove the minimum key of the heap and return its value
        K extractMin();

        // Insert key k into the tree
        void insert(K k);

        // Merge heap H2 into the current heap, destructively
        void merge(BHeap& H2);

        // Print the keys stored in the heap, starting with the smallest binomial tree first
        void printKey();
    
    private:
        HeapNode<K>* _root;
        HeapNode<K>* _revertNode;
        int _size;

        K _sentinel;

        HeapNode<K>* mergeHelper(HeapNode<K>* H1, HeapNode<K>* H2);
        HeapNode<K>* unionHelper(HeapNode<K>* H1, HeapNode<K>* H2);
        void linkHelper(HeapNode<K>* y, HeapNode<K>* z);

        void revert(HeapNode<K>* y);

        void recursivePrint(HeapNode<K>* node);
};