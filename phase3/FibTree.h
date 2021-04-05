
#ifndef _FIBTREE_H_
#define _FIBTREE_H_

#define KEYTYPE int

#include <iostream>

class FibTreeNode
{
    public:
        FibTreeNode* leftSibling = NULL;
        FibTreeNode* rightSibling = NULL;
        FibTreeNode* parent = NULL;
        FibTreeNode* child = NULL;

        bool marked = false;

        KEYTYPE key = 0;
};

class BinomialTree
{
    public:
        int magnitude = 0;
        FibTreeNode* root = NULL;
}

class FibTree
{
    public:

        // Default constructor
        FibTree();

        // Copy constructor
        FibTree& operator=(Fibtree& base);

        // Copy assignment operator
        FibTree(Fibtree& base);

        // Array constructor
        FibTree(KEYTYPE keys[], int n);

        // Destructor
        ~FibTree();

        // Make new empty heap
        //FibTree* MakeHeap();      TODO

        // Insert new value into heap
        void Insert(KEYTYPE value);

        // Get the minimum value in the heap
        KEYTYPE GetMinimum();

        // Get the minimum and remove it from the tree
        KEYTYPE ExtractMin();

        // Meld 2 heaps together - will meld the heap with the heap passed as an argument
        void Union(FibTree* other);

        // Decrease the key of a node in the tree
        void DecreaseKey(KEYTYPE currentValue, KEYTYPE newValue);

        // Delete node from tree 
        void Delete(KEYTYPE value);

        // Get the size of the tree
        int Size();

    private:
        int _size;
        int _numTrees;
        int _numMarked;

        BinomialTree* _minimum;

        // Helper to add a node to the root list
        void AddTreeToRootList(BinomialTree* tree);
}

#endif // !_FIBTREE_H_