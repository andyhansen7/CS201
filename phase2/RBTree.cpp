#include "RBTree.h"

// Default constructor
RBTree::RBTree()
{
    std::cout << "New tree created using default constructor." << std::endl;
}

// Constructor using arrays
RBTree::RBTree(int keys[], int values[], int s)
{
    std::cout << "New tree created using array parameters." << std::endl;

    for(int i = 0; i < s; i++)
    {
        std::cout << "Inserting key " << keys[i] << ", value " << values[i] << std::endl;
        this->insert(keys[i], values[i]);
    }

    std::cout << "Tree creation complete." << std::endl;
}

// Destructor
RBTree::~RBTree()
{

}

// Traditional search method. Returns pointer to value stored at key
int* RBTree::search(int key)
{
    Node* res = RecursiveSearch(_root, key);

    if(res != NULL) return &(res->value);
    else return NULL;
}

// Inserts node with key and value into tree
void RBTree::insert(int key, int value)
{

}

// Removes node with key and returns 1. If key is not found, returns 0
int RBTree::remove(int key)
{

}

// Returns the rank of key in tree, or 0 if key is not found. 
int RBTree::rank(int key)
{

}

// Returns the key of node at position in tree, with 1 being the root
int RBTree::select(int position)
{

}

// Returns pointer to the key following key in the tree, or NULL if none exists
int* RBTree::successor(int key)
{

}

// Returns pointer to the key before key in the tree, or NULL if none exists
int* RBTree::predecessor(int key)
{

}

// Returns size of tree
int RBTree::size()
{
    return _size;
}

// Prints keys in preorder transversal
void RBTree::preorder()
{
    PreorderRecursive(_root);
}

// Prints keys in inorder transversal
void RBTree::inorder()
{
    InorderRecursive(_root);
}

// Prints keys in postorder transversal
void RBTree::postorder()
{
    PostorderRecursive(_root);
}
        
// Prints the smallest k keys in the tree
void RBTree::printk(int k)
{

}

// Recursive search helper
Node* RecursiveSearch(Node* node, int key)
{
    if(node == NULL) return NULL;
    else if(node->key == key) return node;
    else {
        if(key < node->key) return RecursiveSearch(node->leftChild, key);
        else return RecursiveSearch(node->rightChild, key);
    }
}

// Preorder print helper
void RBTree::PreorderRecursive(Node* node)
{
    if(node == NULL) return;

    std::cout << node->key << " ";
    PreorderRecursive(node->leftChild);
    PreorderRecursive(node->rightChild);
}

// Inorder print helper
void RBTree::InorderRecursive(Node* node)
{
    if(node == NULL) return;

    PreorderRecursive(node->leftChild);
    std::cout << node->key << " ";
    PreorderRecursive(node->rightChild);
}

// Postorder print helper
void RBTree::PostorderRecursive(Node* node)
{
    if(node == NULL) return;

    PreorderRecursive(node->leftChild);
    PreorderRecursive(node->rightChild);
    std::cout << node->key << " ";
}