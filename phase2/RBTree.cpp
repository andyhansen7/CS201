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
    // Create new node
    Node* newnode = new Node();
    newnode->key = key;
    newnode->value = value;

    // Tree is empty
    if(_root == NULL) {
        _root = newnode;
        return;
    }
    else {
        RecursiveInsert(_root, newnode);
        return;
    }
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
Node* RBTree::RecursiveSearch(Node* node, int key)
{
    if(node == NULL) return NULL;
    else if(node->key == key) return node;
    else {
        if(key < node->key) return RecursiveSearch(node->leftChild, key);
        else return RecursiveSearch(node->rightChild, key);
    }
}

// Recursive insert helper
void RBTree::RecursiveInsert(Node* root, Node* newnode)
{
    if (newnode->key < root->key) { 
        RecursiveInsert(root->leftChild, newnode); 
        root->leftChild->parent = root; 
    } 
    else if (newnode->key > root->key) { 
        RecursiveInsert(root->rightChild, newnode); 
        root->rightChild->parent = root; 
    } 
    else {
        std::cout << "[ERROR] Insert called on new node with key already in tree" << std::endl;
        return;
    } 
}

// Helper function to fix violations caused by insertion
void RBTree::RecolorTree(Node* newnode)
{
    Node* new_parent = NULL;
    Node* new_grandparent = NULL;

    while( (newnode != _root) && (newnode->color != NodeColor::BLACK) && newnode->parent->color == NodeColor::RED) {

        new_parent = newnode->parent;
        new_grandparent = newnode->parent->parent;

        if(new_parent == new_grandparent->leftChild) {
            Node* new_uncle = new_grandparent->rightChild;

            if(new_uncle != NULL && new_uncle->color == NodeColor::RED) {
                new_grandparent->color = NodeColor::RED;
                new_parent->color = NodeColor::BLACK;
                new_uncle->color = NodeColor::BLACK;
                newnode = new_grandparent;
            }

            else {
                if(newnode == new_parent->rightChild) {
                    LeftRotation(new_parent);
                    newnode = new_parent;
                    new_parent = newnode->parent;
                }

                RightRotation(new_grandparent);

                NodeColor temp = new_parent->color;
                new_parent->color = new_grandparent->color;
                new_grandparent->color = temp;

                newnode = new_parent;
            }
        }

        else {
            Node* new_uncle = new_grandparent->leftChild;

            if(new_uncle != NULL && new_uncle->color == NodeColor::RED) {
                new_grandparent->color = NodeColor::RED;
                new_parent->color = NodeColor::BLACK;
                new_uncle->color = NodeColor::BLACK;
                newnode = new_grandparent;
            }

            else {
                if(newnode == new_parent->leftChild) {
                    RightRotation(new_parent);
                    newnode = new_parent;
                    new_parent = newnode->parent;
                }

                LeftRotation(new_grandparent);

                NodeColor temp = new_parent->color;
                new_parent->color = new_grandparent->color;
                new_grandparent->color = temp;

                newnode = new_parent;
            }
        }
    }

    _root->color = NodeColor::BLACK;
}

// Rotation helpers
void RBTree::LeftRotation(Node* node)
{
    Node* right_child = node->rightChild;
    node->rightChild = right_child->leftChild;

    if(node->rightChild != NULL) node->rightChild->parent = node;

    right_child->parent = node->parent;

    if(node->parent == NULL) _root = right_child;
    else if(node == node->parent->leftChild) node->parent->leftChild = right_child;
    else node->parent->rightChild = right_child;

    right_child->leftChild = node;
    node->parent = right_child;
}

void RBTree::RightRotation(Node* node)
{
    Node* left_child = node->leftChild;
    node->leftChild = left_child->rightChild;

    if(node->leftChild != NULL) node->rightChild->parent = node;

    left_child->parent = node->parent;

    if(node->parent == NULL) _root = left_child;
    else if(node == node->parent->leftChild) node->parent->leftChild = left_child;
    else node->parent->rightChild = left_child;

    left_child->rightChild = node;
    node->parent = left_child;
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