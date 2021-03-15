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

        NodeColor color = NodeColor::RED;
        int rank = 0;
        int numChildrenLeft = 0;
        int numChildrenRight = 0;

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

        // Recursive insert helper
        Node* RecursiveInsert(Node* root, Node* newnode);

        // Helper function to fix violations caused by insertion
        void RecolorTree(Node* newnode);

        // Helper function that returns uncle node
        Node* GetUncle(Node* node);

        // Switches the colors of nodes a and b
        void SwitchColors(Node* a, Node* b);

        // Shifts node down and inserts parent above it
        void ShiftDown(Node* node, Node* parent);

        // Macro to determine if node is left child of parent
        bool IsLeftChild(Node* node);

        // Rotation helpers 
        void LeftRotation(Node* node);
        void RightRotation(Node* node);

        // Helper to get node that will replace node
        Node* GetClosest(Node* node);

        // Successor and predecessor helpers returning reference to a node
        Node* PredecessorNode(Node* node);
        Node* SuccessorNode(Node* node);
        Node* LeftmostNode(Node* root);
        Node* RightmostNode(Node* root);

        // Recursive delete method
        void Delete(Node* node);

        // Double-black correction helper
        void FixDoubleBlack(Node* node);

        // Helper to get sibling of a node
        Node* GetSibling(Node* node);
        
        // Print helpers
        void PreorderRecursive(Node* node);
        void InorderRecursive(Node* node);
        void PostorderRecursive(Node* node);

        // Recursive function to set ranks
        void SetRanks(Node* current, int currentRank);

        // Recursive function to set number of children of node
        void SetChildrenNumbers(Node* current);

        // Recursive select helper
        Node* RecursiveSelect(Node* current, int position);
};  

#endif //_RBTree_H_