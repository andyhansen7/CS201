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
            : key(key)
        {}

        K key;

        HeapNode<K>* parent = NULL;
        HeapNode<K>* child = NULL;
        HeapNode<K>* leftSibling = NULL;
        HeapNode<K>* rightSibling = NULL;
};
template<typename K>
class BinomialTree
{
    public:
        BinomialTree(HeapNode<K>* node, int heapClass)
            : root(node)
        {}
    
        int heapClass = 0;
        HeapNode<K>* root;

        BinomialTree<K>* leftSibling = NULL;
        BinomialTree<K>* rightSibling = NULL;

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
        BinomialTree<K>* _root;
        int _rootListSize;

        K _sentinel;

        void MergeRootList();
        
        void UpdateRoot();

        void RecursivePrint(HeapNode<K>* temp);
};