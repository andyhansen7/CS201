#include "RBTree.h"

// Default constructor
RBTree::RBTree()
{
    //std::cout << "New tree created using default constructor." << std::endl;
}

// Constructor using arrays
RBTree::RBTree(int keys[], int values[], int s)
{
    //std::cout << "New tree created using array parameters." << std::endl;

    for(int i = 0; i < s; i++)
    {
        //std::cout << "Inserting key " << keys[i] << ", value " << values[i] << std::endl;
        this->insert(keys[i], values[i]);
    }

    ///std::cout << "Tree creation complete." << std::endl;
}

// Destructor
RBTree::~RBTree()
{
    //std::cout << "Destructor for tree called." << std::endl;
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
        _root->color = NodeColor::BLACK;
    }

    else {
        Node* check = RecursiveSearch(_root, key);
        if(check != NULL) {
            std::cout << "[ERROR] Insert called on new node with key already in tree" << std::endl;
            return;
        }

        _root = RecursiveInsert(_root, newnode);

        // Fix violations caused by new node insertion
        RecolorTree(newnode);
    }

    _size++;
}

// Removes node with key and returns 1. If key is not found, returns 0
int RBTree::remove(int key)
{
    return 0; // TODO
}

// Returns the rank of key in tree, or 0 if key is not found. 
int RBTree::rank(int key)
{
    // Recursively set ranks of all nodes in tree
    SetRanks(_root, 0);

    Node* node = RecursiveSearch(_root, key);

    if(node != NULL) return node->rank;
    else return 0;
}

// Returns the key of node at position in tree, with 1 being the root
int RBTree::select(int position)
{
    if(position < 1 || position > _size) {
        std::cout << "[ERROR] Call to select() with position out of bounds." << std::endl;
        return 0;
    }
    else {
        SetChildrenNumbers(_root);

        Node* node = RecursiveSelect(_root, position);

        if(node != NULL) return node->key;
        else return 0;
    }
}

// Returns pointer to the key following key in the tree, or NULL if none exists
int* RBTree::successor(int key)
{
    return new int(); // TODO
}

// Returns pointer to the key before key in the tree, or NULL if none exists
int* RBTree::predecessor(int key)
{
    return new int(); // TODO
}

// Returns size of tree
int RBTree::size()
{
    return _size;
}

// Prints keys in preorder transversal
void RBTree::preorder()
{
    if(_root == NULL) return;
    PreorderRecursive(_root);
}

// Prints keys in inorder transversal
void RBTree::inorder()
{
    if(_root == NULL) return;
    InorderRecursive(_root);
}

// Prints keys in postorder transversal
void RBTree::postorder()
{
    if(_root == NULL) return;
    PostorderRecursive(_root);
}
        
// Prints the smallest k keys in the tree
void RBTree::printk(int k)
{
    return; // TODO
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
Node* RBTree::RecursiveInsert(Node* root, Node* newnode)
{
    // Insertion case
    if(root == NULL) return newnode;

    // Insert on left subtree
    if (newnode->key < root->key) { 
        root->leftChild = RecursiveInsert(root->leftChild, newnode); 
        root->leftChild->parent = root; 
    } 
    // Insert on right subtree
    else if (newnode->key > root->key) { 
        root->rightChild = RecursiveInsert(root->rightChild, newnode); 
        root->rightChild->parent = root; 
    } 
    // Something is fucked
    else {
        std::cout << "[ERROR] Insert called on new node with key already in tree" << std::endl;
    } 

    return root;
}

// Helper function to fix violations caused by insertion
void RBTree::RecolorTree(Node* newnode)
{
    // Color root black and end
    if (newnode == _root) {
        newnode->color = NodeColor::BLACK;
        return;
    }
 
    // Create parent, grandparent and uncle nodes for newnode
    Node* parent = newnode->parent;
    Node* grandparent = parent->parent;
    Node* uncle = GetUncle(newnode);
 
    // Black parent
    if(parent->color != NodeColor::BLACK) {

        if(uncle != NULL && uncle->color == NodeColor::RED) {

            // Red uncle - recolor and recurse on grandparent
            parent->color = NodeColor::BLACK;
            uncle->color = NodeColor::BLACK;
            grandparent->color = NodeColor::RED;

            RecolorTree(grandparent);
        }
        else {
            // Parent is left child
            if(IsLeftChild(parent)) {
                // Left-right case
                if(IsLeftChild(newnode)) SwitchColors(parent, grandparent);
                else {
                    LeftRotation(parent);
                    SwitchColors(newnode, grandparent);
                }
                // Left-left and left-right cases
                RightRotation(grandparent);
            }
            // Parent is right child
            else {
                // Right-left case
                if(IsLeftChild(newnode)) {
                    RightRotation(parent);
                    SwitchColors(newnode, grandparent);
                } 
                else SwitchColors(parent, grandparent);
    
            // Right-right and right-left cases
            LeftRotation(grandparent);
            }
        }
    }
}

// Helper function that returns uncle node
Node* RBTree::GetUncle(Node* node)
{
    if(node->parent == NULL || node->parent->parent == NULL) return NULL;

    if(IsLeftChild(node)) return node->parent->parent->rightChild;
    else return node->parent->parent->leftChild;
}

// Switches the colors of nodes a and b
void RBTree::SwitchColors(Node* a, Node* b)
{
    NodeColor temp = a->color;
    a->color = b->color;
    b->color = temp;
}

// Shifts node down and inserts parent above it
void RBTree::ShiftDown(Node* node, Node* node_parent)
{
    if (node->parent != NULL) {
        if (IsLeftChild(node)) node->parent->leftChild = node_parent;
        else node->parent->rightChild = node_parent;
    }

    node_parent->parent = node->parent;
    node->parent = node_parent;
}

// Macro to determine if node is left child of parent
bool RBTree::IsLeftChild(Node* node)
{
    return (node == node->parent->leftChild);
}

// Rotation helpers
void RBTree::LeftRotation(Node* node)
{
    // New parent is right child of node
    Node* node_parent = node->rightChild;
 
    // If node is root, just update it
    if (node == _root) _root = node_parent;

    // The shift
    ShiftDown(node, node_parent);
 
    node->rightChild = node_parent->leftChild;

    if (node_parent->leftChild != NULL) node_parent->leftChild->parent = node;

    node_parent->leftChild = node;
}

void RBTree::RightRotation(Node* node)
{
    // New parent is right child of node
    Node* node_parent = node->leftChild;
 
    // If node is root, just update it
    if (node == _root) _root = node_parent;
 
    // The shift
    ShiftDown(node, node_parent);
 
    node->leftChild = node_parent->rightChild;

    if (node_parent->rightChild != NULL) node_parent->rightChild->parent = node;
 
    node_parent->rightChild = node;
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

    InorderRecursive(node->leftChild);
    std::cout << node->key << " ";
    InorderRecursive(node->rightChild);
}

// Postorder print helper
void RBTree::PostorderRecursive(Node* node)
{
    if(node == NULL) return;

    PostorderRecursive(node->leftChild);
    PostorderRecursive(node->rightChild);
    std::cout << node->key << " ";
}

// Recursive function to set ranks
void RBTree::SetRanks(Node* current, int currentRank) 
{
    current->rank = currentRank + 1;

    if(current->rightChild != NULL) SetRanks(current->rightChild, currentRank + 1);
    if(current->leftChild != NULL) SetRanks(current->leftChild, currentRank + 1);
}

// Recursive function to set number of children of node
void RBTree::SetChildrenNumbers(Node* current)
{
    // Reset values
    current->numChildrenLeft = 0;
    current->numChildrenRight = 0;

    // Recursive calls to children
    if(current->leftChild != NULL) SetChildrenNumbers(current->leftChild);
    if(current->rightChild != NULL) SetChildrenNumbers(current->rightChild);

    // Set number for node
    current->numChildrenLeft = current->leftChild->numChildrenLeft + current->leftChild->numChildrenRight + 1;
}

// Recursive select helper
Node* RBTree::RecursiveSelect(Node* current, int position)
{
    if(current == NULL) return NULL;

    if(current->numChildrenLeft > position) return RecursiveSelect(current->leftChild, position);
    else if(current->numChildrenLeft < position) return RecursiveSelect(current->rightChild, position - current->numChildrenLeft - 1);
    else return current;
}