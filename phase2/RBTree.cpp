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
    std::cout << "Destructor for tree called." << std::endl;
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
        if(check != NULL) return;

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

    if (newnode->key < root->key) { 
        root->leftChild = RecursiveInsert(root->leftChild, newnode); 
        root->leftChild->parent = root; 
    } 
    else if (newnode->key > root->key) { 
        root->rightChild = RecursiveInsert(root->rightChild, newnode); 
        root->rightChild->parent = root; 
    } 
    else {
        std::cout << "[ERROR] Insert called on new node with key already in tree" << std::endl;
    } 

    return root;
}

// Helper function to fix violations caused by insertion
/** OLD
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
**/
// if x is root color it black and return
void RBTree::RecolorTree(Node* newnode)
{
    // if x is root color it black and return
    if (newnode == _root) {
      newnode->color = NodeColor::BLACK;
      return;
    }
 
    // initialize parent, grandparent, uncle
    Node *parent = newnode->parent, *grandparent = parent->parent,
         *uncle = GetUncle(newnode);
 
    if (parent->color != NodeColor::BLACK) {
      if (uncle != NULL && uncle->color == NodeColor::RED) {
        // uncle red, perform recoloring and recurse
        parent->color = NodeColor::BLACK;
        uncle->color = NodeColor::BLACK;
        grandparent->color = NodeColor::RED;
        RecolorTree(grandparent);
      } else {
        // Else perform LR, LL, RL, RR
        if (IsLeftChild(parent)) {
          if (IsLeftChild(newnode)) {
            // for left right
            SwitchColors(parent, grandparent);
          } else {
            LeftRotation(parent);
            SwitchColors(newnode, grandparent);
          }
          // for left left and left right
          RightRotation(grandparent);
        } else {
          if (IsLeftChild(newnode)) {
            // for right left
            RightRotation(parent);
            SwitchColors(newnode, grandparent);
          } else {
            SwitchColors(parent, grandparent);
          }
 
          // for right right and right left
          LeftRotation(grandparent);
        }
      }
    }
}

Node* RBTree::GetUncle(Node* node)
{
    if(node->parent == NULL || node->parent->parent == NULL) return NULL;

    if(node->parent == node->parent->parent->leftChild) return node->parent->parent->rightChild;
    else return node->parent->parent->leftChild;
}

void RBTree::SwitchColors(Node* a, Node* b)
{
    NodeColor temp = a->color;
    a->color = b->color;
    b->color = temp;
}

void RBTree::ShiftDown(Node* node, Node* parent)
{
    if(node->parent != NULL) {
      if (IsLeftChild(node)) {
        node->parent->leftChild = parent;
      } else {
        node->parent->rightChild = parent;
      }
    }
    parent->parent = node->parent;
    node->parent = parent;
}

bool RBTree::IsLeftChild(Node* node)
{
    return (node == node->parent->leftChild);
}

// Rotation helpers
void RBTree::LeftRotation(Node* node)
{
   // new parent will be node's right child
    Node *nParent = node->rightChild;
 
    // update root if current node is root
    if (node == _root)
      _root = nParent;
 
    ShiftDown(node, nParent);
 
    // connect x with new parent's left element
    node->rightChild = nParent->leftChild;
    // connect new parent's left element with node
    // if it is not null
    if (nParent->leftChild != NULL)
      nParent->leftChild->parent = node;
 
    // connect new parent with x
    nParent->leftChild = node;
}

void RBTree::RightRotation(Node* node)
{
   // new parent will be node's left child
    Node *nParent = node->leftChild;
 
    // update root if current node is root
    if (node == _root)
      _root = nParent;
 
    ShiftDown(node, nParent);
 
    // connect x with new parent's right element
    node->leftChild = nParent->rightChild;
    // connect new parent's right element with node
    // if it is not null
    if (nParent->rightChild != NULL)
      nParent->rightChild->parent = node;
 
    // connect new parent with x
    nParent->rightChild = node;
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