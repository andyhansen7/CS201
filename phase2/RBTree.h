/* ==========================
 * Red - Black Tree 
 * CS201-001 Spring 2021
 * Developed by Andrew Hansen
 * arhansen@crimson.ua.edu
 * ===========================
 */

#ifndef _RBTree_H_
#define _RBTree_H_

#include <iostream>
#include <string>

enum class NodeColor {
    RED = 0,
    BLACK
};

template<typename K, typename V>
class Node {
    public:
        K key;
        V value;

        NodeColor color = NodeColor::RED;
        int rank = 0;
        int nodeSize = 0;

        Node<K, V>* leftChild = NULL;
        Node<K, V>* rightChild = NULL;
        Node<K, V>* parent = NULL;
};

template<typename K, typename V>
class RBTree
{
    public:
        // Default constructor
        RBTree();

        // Constructor using arrays
        RBTree(K keys[], V values[], int s);

        // Traditional copy constructor
        RBTree& operator=(RBTree& tree);

        // Traditional copy assignment operator
        RBTree(RBTree& tree);

        // Destructor
        ~RBTree();

        // Traditional search method. Returns pointer to value stored at key
        V* search(K key);

        // Inserts node with key and value into tree
        void insert(K key, V value);

        // Removes node with key and returns 1. If key is not found, returns 0
        int remove(K key);

        // Returns the rank of key in tree, or 0 if key is not found. 
        int rank(K key);

        // Returns the key of node at position in tree, with 1 being the root
        K select(int position);

        // Returns pointer to the key following key in the tree, or NULL if none exists
        K* successor(K key);

        // Returns pointer to the key before key in the tree, or NULL if none exists
        K* predecessor(K key);

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
        Node<K, V>* _root = NULL;

        int _size = 0;

        // Recursive search helper
        Node<K, V>* RecursiveSearch(Node<K, V>* node, K key);

        // Recursive insert helper
        Node<K, V>* RecursiveInsert(Node<K, V>* root, Node<K, V>* newnode);

        // Helper function to fix violations caused by insertion
        void RecolorTree(Node<K, V>* newnode);

        // Helper function that returns uncle node
        Node<K, V>* GetUncle(Node<K, V>* node);

        // Switches the colors of nodes a and b
        void SwitchColors(Node<K, V>* a, Node<K, V>* b);

        // Shifts node down and inserts parent above it
        void ShiftDown(Node<K, V>* node, Node<K, V>* parent);

        // Macro to determine if node is left child of parent
        bool IsLeftChild(Node<K, V>* node);

        // Rotation helpers 
        void LeftRotation(Node<K, V>* node);
        void RightRotation(Node<K, V>* node);

        // Helper to get node that will replace node
        Node<K, V>* GetClosest(Node<K, V>* node);

        // Successor and predecessor helpers returning reference to a node
        Node<K, V>* PredecessorNode(Node<K, V>* node);
        Node<K, V>* SuccessorNode(Node<K, V>* node);
        Node<K, V>* LeftmostNode(Node<K, V>* root);
        Node<K, V>* RightmostNode(Node<K, V>* root);

        // Recursive delete method
        void Delete(Node<K, V>* node);

        // Double-black correction helper
        void FixDoubleBlack(Node<K, V>* node);

        // Helper to get sibling of a node
        Node<K, V>* GetSibling(Node<K, V>* node);
        
        // Print helpers
        void PreorderRecursive(Node<K, V>* node);
        void InorderRecursive(Node<K, V>* node);
        void PostorderRecursive(Node<K, V>* node);

        // Recursive function to set ranks
        void SetRanks(Node<K, V>* current, int currentRank);

        // Recursive select helper
        Node<K, V>* RecursiveSelect(Node<K, V>* current, int position);

        // Node size helper
        int GetNodeSize(Node<K, V>* node);

        // Rank helper
        int RankOf(Node<K, V>* node);
        int RecursiveRank(Node<K, V>* current, K key);
};  

#endif //_RBTree_H_