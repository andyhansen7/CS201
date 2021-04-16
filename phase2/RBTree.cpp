/* ==========================
 * Red - Black Tree 
 * CS201-001 Spring 2021
 * Developed by Andrew Hansen
 * arhansen@crimson.ua.edu
 * ===========================
 */

#ifndef __RBTREE_CPP__
#define __RBTREE_CPP__

#include "RBTree.h"

// Default constructor
template<typename K, typename V>
RBTree<K, V>::RBTree()
{
    
}

// Constructor using arrays
template<typename K, typename V>
RBTree<K, V>::RBTree(K keys[], V values[], int s)
{
    for(int i = 0; i < s; i++)
    {
        insert(keys[i], values[i]);
    }
}

// Traditional copy constructor
template<typename K, typename V>
RBTree<K, V>& RBTree<K, V>::operator=(RBTree<K, V>& tree)
{
    for(int i = 0; i < tree.size(); i++) {
        K key = tree.select(i + 1);
        V val = *(tree.search(key));

        insert(key, val);
    }

    return *this;
}

// Traditional copy assignment operator
template<typename K, typename V>
RBTree<K, V>::RBTree(RBTree<K, V>& tree)
{
    for(int i = 0; i < tree.size(); i++) {
        K key = tree.select(i + 1);
        V val = *(tree.search(key));

        insert(key, val);
    }
}

// Destructor
template<typename K, typename V>
RBTree<K, V>::~RBTree()
{
    //std::cout << "Destructor for tree called." << std::endl;
}

// Traditional search method. Returns pointer to value stored at key
template<typename K, typename V>
V* RBTree<K, V>::search(K key)
{
    Node<K, V>* res = RecursiveSearch(_root, key);

    if(res != NULL) return &(res->value);
    else return NULL;
}

// Inserts node with key and value into tree
template<typename K, typename V>
void RBTree<K, V>::insert(K key, V value)
{
    // Create new node
    Node<K, V>* newnode = new Node<K, V>();
    newnode->key = key;
    newnode->value = value;

    // Tree is empty
    if(_root == NULL) {
        _root = newnode;
        _root->color = NodeColor::BLACK;
    }

    else {
        Node<K, V>* check = RecursiveSearch(_root, key);
        if(check != NULL) {
            //std::cout << "[ERROR] Insert called on new node with key already in tree" << std::endl;
            return;
        }

        _root = RecursiveInsert(_root, newnode);

        // Fix violations caused by new node insertion
        RecolorTree(newnode);
    }

    _size++;
}

// Removes node with key and returns 1. If key is not found, returns 0
template<typename K, typename V>
int RBTree<K, V>::remove(K key)
{
    // Empty tree
    if(_root == NULL) return 0;
 
    Node<K, V>* search = RecursiveSearch(_root, key);

    if(search == NULL) {
        //std::cout << "[ERROR] Node with key could not be found and removed" << std::endl;
        return 0;
    }
    else {
        Delete(search);
        _size--;
        return 1;
    }
}

// Returns the rank of key in tree, or 0 if key is not found. 
template<typename K, typename V>
int RBTree<K, V>::rank(K key)
{   
    return 1 + RecursiveRank(_root, key);
}

// Returns the key of node at position in tree, with 1 being the root
template<typename K, typename V>
K RBTree<K, V>::select(int position)
{
    if(position < 1 || position > _size) {
        //std::cout << "[ERROR] Call to select() with position out of bounds." << std::endl;
        return _root->key;
    }
    else {
        Node<K, V>* node = RecursiveSelect(_root, position - 1);

        if(node != NULL) return node->key;
        else return _root->key;
    }
}

// Returns pointer to the key following key in the tree, or NULL if none exists
template<typename K, typename V>
K* RBTree<K, V>::successor(K key)
{
    Node<K, V>* search = RecursiveSearch(_root, key);

    if(search == NULL) return NULL;

    else {
        Node<K, V>* sucessor = SuccessorNode(search);
        return &(sucessor->key);
    }
}

// Returns pointer to the key before key in the tree, or NULL if none exists
template<typename K, typename V>
K* RBTree<K, V>::predecessor(K key)
{
    Node<K, V>* search = RecursiveSearch(_root, key);

    if(search == NULL) return NULL;

    else {
        Node<K, V>* sucessor = PredecessorNode(search);
        return &(sucessor->key);
    }
}

// Returns size of tree
template<typename K, typename V>
int RBTree<K, V>::size()
{
    return _size;
}

// Prints keys in preorder transversal
template<typename K, typename V>
void RBTree<K, V>::preorder()
{
    if(_root == NULL) return;
    PreorderRecursive(_root);
    std::cout << std::endl;
}

// Prints keys in inorder transversal
template<typename K, typename V>
void RBTree<K, V>::inorder()
{
    if(_root == NULL) return;
    InorderRecursive(_root);
    std::cout << std::endl;
}

// Prints keys in postorder transversal
template<typename K, typename V>
void RBTree<K, V>::postorder()
{
    if(_root == NULL) return;
    PostorderRecursive(_root);
    std::cout << std::endl;
}
        
// Prints the smallest k keys in the tree
template<typename K, typename V>
void RBTree<K, V>::printk(int k)
{
    for(int i = 1; i <= k; i++)
    {
        std::cout << select(i) << " ";
    }
    std::cout << std::endl;
}

// Recursive search helper
template<typename K, typename V>
Node<K, V>* RBTree<K, V>::RecursiveSearch(Node<K, V>* node, K key)
{
    if(node == NULL) return NULL;
    else if(node->key == key) return node;
    else {
        if(key < node->key) return RecursiveSearch(node->leftChild, key);
        else return RecursiveSearch(node->rightChild, key);
    }
}

// Recursive insert helper
template<typename K, typename V>
Node<K, V>* RBTree<K, V>::RecursiveInsert(Node<K, V>* root, Node<K, V>* newnode)
{
    // Insertion case
    if(root == NULL) return newnode;

    // Insert on left subtree
    if(newnode->key < root->key) { 
        root->numLeft++;
        root->leftChild = RecursiveInsert(root->leftChild, newnode); 
        root->leftChild->parent = root; 
    } 
    // Insert on right subtree
    else if(newnode->key > root->key) { 
        root->numRight++;
        root->rightChild = RecursiveInsert(root->rightChild, newnode); 
        root->rightChild->parent = root; 
    } 
    // Error case
    else {
        //std::cout << "[ERROR] Insert called on new node with key already in tree" << std::endl;
    } 

    return root;
}

// Helper function to fix violations caused by insertion
template<typename K, typename V>
void RBTree<K, V>::RecolorTree(Node<K, V>* newnode)
{
    // Color root black and end
    if (newnode == _root) {
        newnode->color = NodeColor::BLACK;
        return;
    }
 
    // Create parent, grandparent and uncle nodes for newnode
    Node<K, V>* parent = newnode->parent;
    Node<K, V>* grandparent = parent->parent;
    Node<K, V>* uncle = GetUncle(newnode);
 
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
template<typename K, typename V>
Node<K, V>* RBTree<K, V>::GetUncle(Node<K, V>* node)
{
    if(node->parent == NULL || node->parent->parent == NULL) return NULL;

    if(IsLeftChild(node)) return node->parent->parent->rightChild;
    else return node->parent->parent->leftChild;
}

// Switches the colors of nodes a and b
template<typename K, typename V>
void RBTree<K, V>::SwitchColors(Node<K, V>* a, Node<K, V>* b)
{
    NodeColor temp = a->color;
    a->color = b->color;
    b->color = temp;
}

// Shifts node down and inserts parent above it
template<typename K, typename V>
void RBTree<K, V>::ShiftDown(Node<K, V>* node, Node<K, V>* node_parent)
{
    if(node->parent != NULL) {
        if (IsLeftChild(node)) node->parent->leftChild = node_parent;
        else node->parent->rightChild = node_parent;
    }

    node_parent->parent = node->parent;
    node->parent = node_parent;
}

// Macro to determine if node is left child of parent
template<typename K, typename V>
bool RBTree<K, V>::IsLeftChild(Node<K, V>* node)
{
    if(node->parent == NULL) return false;
    return (node == node->parent->leftChild);
}

// Rotation helpers
template<typename K, typename V>
void RBTree<K, V>::LeftRotation(Node<K, V>* node)
{
    // New parent is right child of node
    Node<K, V>* node_parent = node->rightChild;
 
    // If node is root, just update it
    if(node == _root) _root = node_parent;

    // The shift
    ShiftDown(node, node_parent);
 
    node->rightChild = node_parent->leftChild;

    if(node_parent->leftChild != NULL) node_parent->leftChild->parent = node;

    node_parent->leftChild = node;

    // Update children counts
    UpdateChildren(node->leftChild);
    UpdateChildren(node->rightChild);
    UpdateChildren(node);

    Node<K, V>* temp = GetSibling(node);
    if(temp != NULL) {
        UpdateChildren(temp->leftChild);
        UpdateChildren(temp->rightChild);
        UpdateChildren(temp);
    }

    //UpdateChildren(node_parent->leftChild);
    UpdateChildren(node_parent->rightChild);
    
    temp = node_parent;
    while(temp != NULL) {
        UpdateChildren(temp->rightChild);
        UpdateChildren(temp->leftChild);
        UpdateChildren(temp);

        temp = temp->parent;
    }
}

template<typename K, typename V>
void RBTree<K, V>::RightRotation(Node<K, V>* node)
{
    // New parent is right child of node
    Node<K, V>* node_parent = node->leftChild;
 
    // If node is root, just update it
    if(node == _root) _root = node_parent;
 
    // The shift
    ShiftDown(node, node_parent);
 
    node->leftChild = node_parent->rightChild;

    if(node_parent->rightChild != NULL) node_parent->rightChild->parent = node;
 
    node_parent->rightChild = node;

    // Update children counts
    UpdateChildren(node->leftChild);
    UpdateChildren(node->rightChild);
    UpdateChildren(node);

    Node<K, V>* temp = GetSibling(node);
    if(temp != NULL) {
        UpdateChildren(temp->leftChild);
        UpdateChildren(temp->rightChild);
        UpdateChildren(temp);
    }

    UpdateChildren(node_parent->leftChild);
    //UpdateChildren(node_parent->rightChild);

    temp = node_parent;
    while(temp != NULL) {
        UpdateChildren(temp);
        temp = temp->parent;
    }
}

template<typename K, typename V>
// Helper to get node that will replace node
Node<K, V>* RBTree<K, V>::GetClosest(Node<K, V>* node)
{
    // If node has 2 children
    if(node->leftChild != NULL && node->rightChild != NULL) return RightmostNode(node->leftChild);//return LeftmostNode(node->rightChild);
 
    // If node is leaf node
    else if(node->leftChild == NULL && node->rightChild == NULL) return NULL;
 
    // Node has only one child
    if(node->leftChild != NULL) return node->leftChild;
    else return node->rightChild;
}

// Successor and predecessor helpers returning reference to a node
template<typename K, typename V>
Node<K, V>* RBTree<K, V>::PredecessorNode(Node<K, V>* node)
{
    if(node->leftChild != NULL) return RightmostNode(node->leftChild);

    Node<K, V>* parent = node->parent;
    Node<K, V>* temp = node;

    while(parent != NULL && temp == parent->leftChild) {
        temp = parent;
        parent = parent->parent;
    }

    return parent;
}

template<typename K, typename V>
Node<K, V>* RBTree<K, V>::SuccessorNode(Node<K, V>* node)
{
    if(node->rightChild != NULL) return LeftmostNode(node->rightChild);

    Node<K, V>* parent = node->parent;
    Node<K, V>* temp = node;

    while(parent != NULL && temp == parent->rightChild) {
        temp = parent;
        parent = parent->parent;
    }

    return parent;
}

template<typename K, typename V>
Node<K, V>* RBTree<K, V>::LeftmostNode(Node<K, V>* root)
{
    Node<K, V>* temp = root;
 
    while(temp->leftChild != NULL) temp = temp->leftChild;
 
    return temp;
}

template<typename K, typename V>
Node<K, V>* RBTree<K, V>::RightmostNode(Node<K, V>* root)
{
    Node<K, V>* temp = root;
 
    while(temp->rightChild != NULL) temp = temp->rightChild;
 
    return temp;
}

// Recursive delete method
template<typename K, typename V>
void RBTree<K, V>::Delete(Node<K, V>* node)
{
    Node<K, V>* replacementnode = GetClosest(node);
    Node<K, V>* parent = node->parent;
 
    // Both node and its replacement are black
    bool doubleblack = ((replacementnode == NULL || replacementnode->color == NodeColor::BLACK) && (node->color == NodeColor::BLACK));
 
    // Node is a leaf node
    if(replacementnode == NULL) {
        // Reset root if it is being deleted
        if(node == _root) _root = NULL;
        
        else {
            // Fix double black case
            if(doubleblack) FixDoubleBlack(node);

            // One of them is red
            else {
                // Set sibling to red
                if(GetSibling(node) != NULL) GetSibling(node)->color = NodeColor::RED;
            }
 
            // Delete node from tree
            if(IsLeftChild(node)) {
                parent->leftChild = NULL;
                parent->numLeft = 0;

                // Propogate upwards
                Node<K, V>* temp = parent->parent;
                while(temp != NULL) {
                    UpdateChildren(temp);
                    temp = temp->parent;
                }
            }
            else {
                parent->rightChild = NULL;
                parent->numRight = 0;

                // Propogate upwards
                Node<K, V>* temp = parent->parent;
                while(temp != NULL) {
                    UpdateChildren(temp);
                    temp = temp->parent;
                }
            }
        }
        
        delete node;
        return;
    }
    
    // Node has only one child
    if((node->leftChild == NULL) || (node->rightChild == NULL)) {

        // Node is root, replace values
        if(node == _root) {
            node->key = replacementnode->key;
            node->value = replacementnode->value;
            node->leftChild = NULL;
            node->rightChild = NULL;
            node->numLeft = 0;
            node->numRight = 0;

            delete replacementnode;
        } 

        // Detach node from tree
        else {
            if(IsLeftChild(node)) {
                parent->leftChild = replacementnode;

                Node<K, V>* left = replacementnode->leftChild;
                Node<K, V>* right = replacementnode->rightChild;

                UpdateChildren(left);
                UpdateChildren(right);
                UpdateChildren(replacementnode);
                UpdateChildren(parent);
                
                // Propogate upwards
                Node<K, V>* temp = parent->parent;
                while(temp != NULL) {
                    UpdateChildren(temp);
                    temp = temp->parent;
                }
            }
            else {
                parent->rightChild = replacementnode;
                
                Node<K, V>* left = replacementnode->leftChild;
                Node<K, V>* right = replacementnode->rightChild;

                UpdateChildren(left);
                UpdateChildren(right);
                UpdateChildren(replacementnode);
                UpdateChildren(parent);
                
                // Propogate upwards
                Node<K, V>* temp = parent->parent;
                while(temp != NULL) {
                    UpdateChildren(temp);
                    temp = temp->parent;
                }
            }
            
            replacementnode->parent = parent;
            delete node;

            // Check and fix double-black
            if(doubleblack) FixDoubleBlack(replacementnode);
            // Recolor replacement node
            else replacementnode->color = NodeColor::BLACK;
        }
      
        return;
    }
 
    // Swap replacement and node values and recurse
    K tempkey = node->key;
    V tempval = node->value;

    node->key = replacementnode->key;
    node->value = replacementnode->value;

    replacementnode->key = tempkey;
    replacementnode->value = tempval;

    Delete(replacementnode);
}

// Double-black correction helper
template<typename K, typename V>
void RBTree<K, V>::FixDoubleBlack(Node<K, V>* node)
{
    // Exit if at root
    if(node == _root) return;
 
    Node<K, V>* sibling = GetSibling(node);

    // If no sibling, recurse on parent
    if(sibling == NULL) FixDoubleBlack(node->parent);

    else {
        // Red sibling
        if(sibling->color == NodeColor::RED) {
            node->parent->color = NodeColor::RED;
            sibling->color = NodeColor::BLACK;

            // Left case
            if(IsLeftChild(sibling)) RightRotation(node->parent);
            // Right case 
            else LeftRotation(node->parent);

            // Recurse 
            FixDoubleBlack(node);
        }

        // Black sibling 
        else {
            if( (sibling->leftChild != NULL && sibling->leftChild->color == NodeColor::RED) || (sibling->rightChild != NULL && sibling->rightChild->color == NodeColor::RED) ) {

                // Red left child
                if(sibling->leftChild != NULL && sibling->leftChild->color == NodeColor::RED) {

                    // Node is right child
                    if(IsLeftChild(sibling)) {
                        sibling->leftChild->color = sibling->color;
                        sibling->color = node->parent->color;

                        RightRotation(node->parent);
                    } 
                    
                    // Node is left child
                    else {
                        sibling->leftChild->color = node->parent->color;

                        RightRotation(sibling);
                        LeftRotation(node->parent);
                    }
                }
                else {

                    // Node is right child
                    if(IsLeftChild(sibling)) {
                        sibling->rightChild->color = node->parent->color;

                        LeftRotation(sibling);
                        RightRotation(node->parent);
                    }
                    else {
                        sibling->rightChild->color = sibling->color;
                        sibling->color = node->parent->color;

                        LeftRotation(node->parent);
                    }
                }

                node->parent->color = NodeColor::BLACK;
            }

            // Both children black
            else {
                sibling->color = NodeColor::RED;

                // Check and fix double black case
                if(node->parent->color == NodeColor::BLACK) FixDoubleBlack(node->parent);
                else node->parent->color = NodeColor::BLACK;
            }
        }
    }
}

// Helper to get sibling of a node
template<typename K, typename V>
Node<K, V>* RBTree<K, V>::GetSibling(Node<K, V>* node)
{
    if(node->parent == NULL) return NULL;
    else if(IsLeftChild(node)) return node->parent->rightChild;
    else return node->parent->leftChild;
}

// Preorder print helper
template<typename K, typename V>
void RBTree<K, V>::PreorderRecursive(Node<K, V>* node)
{
    if(node == NULL) return;

    std::cout << node->key << " ";
    PreorderRecursive(node->leftChild);
    PreorderRecursive(node->rightChild);
}

// Inorder print helper
template<typename K, typename V>
void RBTree<K, V>::InorderRecursive(Node<K, V>* node)
{
    if(node == NULL) return;

    InorderRecursive(node->leftChild);
    std::cout << node->key << " ";
    InorderRecursive(node->rightChild);
}

// Postorder print helper
template<typename K, typename V>
void RBTree<K, V>::PostorderRecursive(Node<K, V>* node)
{
    if(node == NULL) return;

    PostorderRecursive(node->leftChild);
    PostorderRecursive(node->rightChild);
    std::cout << node->key << " ";
}

// Recursive helper to select a node at the specified position in the tree
template<typename K, typename V>
Node<K, V>* RBTree<K, V>::RecursiveSelect(Node<K, V>* current, int position)
{
    if(current == NULL) return NULL;

    UpdateChildren(current);
    UpdateChildren(current->leftChild);
    UpdateChildren(current->rightChild);

    int numlower = current->numLeft;

    if(numlower > position) return RecursiveSelect(current->leftChild, position);
    else if(numlower < position) return RecursiveSelect(current->rightChild, position - numlower - 1);
    else return current;
}

// Returns the size of a node, i.e. the number of children it has plus one
template<typename K, typename V>
int RBTree<K, V>::GetNodeSize(Node<K, V>* node)
{
    if(node == NULL) return 0;

    // New method in O(1) time
    return (1 + node->numLeft + node->numRight);
}

// Recursively finds the rank of a node with key
template<typename K, typename V>
int RBTree<K, V>::RecursiveRank(Node<K, V>* current, K key)
{
    if(current == NULL) return 0;

    if(current->key > key) return RecursiveRank(current->leftChild, key);
    else if (current->key < key) return 1 + GetNodeSize(current->leftChild) + RecursiveRank(current->rightChild, key); 
    else return GetNodeSize(current->leftChild); 
}

// Helper to update counts of children, when a node is repositioned in the tree. Non-recursive
template<typename K, typename V>
void RBTree<K, V>::UpdateChildren(Node<K, V>* node)
{
    if(node == NULL) return;

    node->numLeft = 0;
    node->numRight = 0;

    if(node->leftChild != NULL) node->numLeft = node->leftChild->numLeft + node->leftChild->numRight + 1;
    if(node->rightChild != NULL) node->numRight = node->rightChild->numLeft + node->rightChild->numRight + 1;
}

#endif // !__RBTREE_CPP__