#ifndef _RBTree_H_
#define _RBTree_H_

#include <iostream>
#include <string>

enum class NodeColor {
    RED = 0,
    BLACK
};

class Node {
    public:
        int key = 0;
        int value = 0;
        NodeColor color = NodeColor::BLACK;
        Node* leftChild = NULL;
        Node* rightChild = NULL;
        Node* parent = NULL;

        void FreeNode() 
        {
            if(leftChild != NULL) leftChild->FreeNode();
            if(rightChild != NULL) rightChild->FreeNode();

            
        }
};

class RBTree
{
    public:
        // Default constructor
        RBTree();

        // Constructor using arrays
        RBTree(int keys[], int values[], int s);

        // Destructor
        ~RBTree();

        // Traditional search method. Returns pointer to value stored at key
        int* search(int key);

        // Inserts node with key and value into tree
        void insert(int key, int value);

        // Removes node with key and returns 1. If key is not found, returns 0
        int remove(int key);

        // Returns the rank of key in tree, or 0 if key is not found. 
        int rank(int key);

        // Returns the key of node at position in tree, with 1 being the root
        int select(int position);

        // Returns pointer to the key following key in the tree, or NULL if none exists
        int* successor(int key);

        // Returns pointer to the key before key in the tree, or NULL if none exists
        int* predecessor(int key);

        // Returns size of tree
        int size();

        // Prints keys in preorder transversal
        void preorder();

        // Prints keys in inorder transversal
        void inorder();

        // Prints keys in postorder transversal
        void postorder();
        
        // Prints the smallest k keys in the tree
        void printk(int k);
    
    private:
        Node* _root = NULL;

        int _size = 0;

        // Recursive search helper
        Node* RecursiveSearch(Node* node, int key);

        // Print helpers
        void PreorderRecursive(Node* node);
        void InorderRecursive(Node* node);
        void PostorderRecursive(Node* node);
};  

#endif //_RBTree_H_