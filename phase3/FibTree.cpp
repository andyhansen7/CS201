#include "FibTree.h"

using namespace std;

// Default constructor
FibTree::FibTree()
    : _size(0), _numTrees(0), _numMarked(0), _minimum(NULL)
{
    std::cout << "Empty FibTree created using default constructor" << std::endl;
}

// Copy assignment operator
FibTree& FibTree::operator=(Fibtree& base)
    : _size(0), _numTrees(0), _numMarked(0), _minimum(NULL)
{

    // Clear current values
    while(_size > 0) ExtractMin();

    // Copy new values
    for(int i = 0; i < base->Size(); i++)
    {
        Insert(base->ExtractMin());
    }

    std::cout << "Fibtree created using copy assignment operator" << std::endl;

    return *this;
}

// Copy constructor
FibTree::FibTree(Fibtree& base)
    : _size(0), _numTrees(0), _numMarked(0), _minimum(NULL) 
{
    // Insert new values
    for(int i = 0; i < base->Size(); i++)
    {
        Insert(base->ExtractMin());
    }

    std::cout << "Fibtree created using copy constructor" << std::endl;
}

// Array constructor
FibTree::FibTree(KEYTYPE keys[], int n)
    : _size(0), _numTrees(0), _numMarked(0), _minimum(NULL)
{
    for(int i = 0; i < n; i++)
    {
        Insert(keys[i]);
    }

    std::cout << "FibTree created using array constructor" << std::endl;
}

// Destructor
FibTree::~FibTree()
{
    std::cout << "Destructor called for FibTree. Goodbye!" << std::endl;
}

/*  TODO
// Make new empty heap
FibTree::FibTree* MakeHeap()
{

}
*/

// Insert new value into heap
void FibTree::Insert(KEYTYPE value)
{
    // Create new node object
    FibTreeNode* newnode = new FibTreeNode();
    newnode->key = value;

    // Create new binomial tree
    BinomialTree* newtree = new BinomialTree();
    newtree->magnitude = 0;
    newtree->root = newnode;

    // Add new node to root list

}

// Get the minimum value in the heap
KEYTYPE FibTree::GetMinimum()
{

}

// Get the minimum and remove it from the tree
KEYTYPE FibTree::ExtractMin()
{

}

// Meld 2 heaps together - will meld the heap with the heap passed as an argument
void FibTree::Union(FibTree* other)
{

}

// Decrease the key of a node in the tree
void FibTree::DecreaseKey(KEYTYPE currentValue, KEYTYPE newValue)
{

}

// Delete node from tree 
void FibTree::Delete(KEYTYPE value)
{

}

// Get the size of the tree
int FibTree::Size()
{
    return _size;
}

// Helper to add a node to the root list
void FibTree::AddTreeToRootList(BinomialTree* tree)
{
    // Insert tree into linked list as right sibling of minimum
    _minimum->root->rightSibling->leftSibling = tree->root;
    tree->root->rightSibling = _minimum->root->rightSibling;

    _minimum->root->rightSibling = tree->root;
    tree->root->leftSibling = _minimum->root;

    // Update minimum if new tree is less than min
    if(tree->root->key < _minimum->root->key)
    {
        _minimum = tree;
    }

    // Update counts
    _numTrees++;   

    // Fix marked
    tree->root->marked = false;
}