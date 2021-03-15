#include "RBTree.h"

// Default constructor
template<typename K, typename V>
RBTree<K, V>::RBTree()
{
    //std::cout << "New tree created using default constructor." << std::endl;
}

// Constructor using arrays
template<typename K, typename V>
RBTree<K, V>::RBTree(K keys[], V values[], int s)
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
template<typename K, typename V>
int RBTree<K, V>::remove(K key)
{
    // Empty tree
    if(_root == NULL) return 0;
 
    Node<K, V>* search = RecursiveSearch(_root, key);

    if(search == NULL) {
        std::cout << "[ERROR] Node with key could not be found and removed" << std::endl;
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
    // Recursively set ranks of all nodes in tree
    SetRanks(_root, 0);

    Node<K, V>* node = RecursiveSearch(_root, key);

    if(node != NULL) return node->rank;
    else return 0;
}

// Returns the key of node at position in tree, with 1 being the root
template<typename K, typename V>
int RBTree<K, V>::select(int position)
{
    if(position < 1 || position > _size) {
        std::cout << "[ERROR] Call to select() with position out of bounds." << std::endl;
        return 0;
    }
    else {
        SetChildrenNumbers(_root);

        Node<K, V>* node = RecursiveSelect(_root, position);

        if(node != NULL) return node->key;
        else return 0;
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
}

// Prints keys in inorder transversal
template<typename K, typename V>
void RBTree<K, V>::inorder()
{
    if(_root == NULL) return;
    InorderRecursive(_root);
}

// Prints keys in postorder transversal
template<typename K, typename V>
void RBTree<K, V>::postorder()
{
    if(_root == NULL) return;
    PostorderRecursive(_root);
}
        
// Prints the smallest k keys in the tree
template<typename K, typename V>
void RBTree<K, V>::printk(int k)
{
    return; // TODO
}

// Recursive search helper
template<typename K, typename V>
Node<K, V>* RBTree<K, V>::RecursiveSearch(Node<K, V>* node, int key)
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
    if (node->parent != NULL) {
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
    return (node == node->parent->leftChild);
}

// Rotation helpers
template<typename K, typename V>
void RBTree<K, V>::LeftRotation(Node<K, V>* node)
{
    // New parent is right child of node
    Node<K, V>* node_parent = node->rightChild;
 
    // If node is root, just update it
    if (node == _root) _root = node_parent;

    // The shift
    ShiftDown(node, node_parent);
 
    node->rightChild = node_parent->leftChild;

    if (node_parent->leftChild != NULL) node_parent->leftChild->parent = node;

    node_parent->leftChild = node;
}

template<typename K, typename V>
void RBTree<K, V>::RightRotation(Node<K, V>* node)
{
    // New parent is right child of node
    Node<K, V>* node_parent = node->leftChild;
 
    // If node is root, just update it
    if (node == _root) _root = node_parent;
 
    // The shift
    ShiftDown(node, node_parent);
 
    node->leftChild = node_parent->rightChild;

    if (node_parent->rightChild != NULL) node_parent->rightChild->parent = node;
 
    node_parent->rightChild = node;
}

template<typename K, typename V>
// Helper to get node that will replace node
Node<K, V>* RBTree<K, V>::GetClosest(Node<K, V>* node)
{
    // If node has 2 children
    if(node->leftChild != NULL && node->rightChild != NULL) return SuccessorNode(node->rightChild);
 
    // If node is leaf node
    else if(node->leftChild == NULL && node->rightChild == NULL) return NULL;
 
    // Node has only one child
    else {
        if(node->leftChild != NULL) return node->leftChild;
        else return node->rightChild;
    }
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

/*{
    Node<K, V>* replacement = GetClosest(node);
    
    // No predecesor to node to be replaced
    if(replacement == NULL) {
        // Simply remove root if node is root
        if(node == _root) _root = NULL;

        else {
            // Check for double-black case and fix
            if((replacement->color == NodeColor::BLACK) && (node == NULL || node->color == NodeColor::BLACK)) FixDoubleBlack(node); // TODO

            // Recolor sibling if one exists
            else {
                if((IsLeftChild(node) && node->parent->rightChild != NULL)) node->parent->rightChild->color = NodeColor::RED;
                else if((!IsLeftChild(node) && node->parent->leftChild != NULL)) node->parent->leftChild->color = NodeColor::RED;
            }   

            // Perform deletion
            if(IsLeftChild(node)) node->parent->leftChild = NULL;
            else node->parent->rightChild = NULL;
        }
        
        delete node;
        return;
    }
    
    // Node has less than 2 children
    if(node->leftChild == NULL || node->rightChild == NULL) {
        // Node is root - swap values and delete child
        if(node == _root) {
            node->key = replacement->key;
            node->value = replacement->value;
            node->leftChild = NULL;
            node->rightChild = NULL;

            delete replacement;
        }
        // Switch node and replacement
        else {
            if(IsLeftChild(node)) node->parent->leftChild = replacement;
            else node->parent->rightChild = replacement;

            replacement->parent = node->parent;

            delete node;

            // Check for double black case and fix
            if((replacement->color == NodeColor::BLACK) && (node == NULL || node->color == NodeColor::BLACK)) FixDoubleBlack(replacement);
            else replacement->color = NodeColor::BLACK;
        }

        return;
    }

    // Node has 2 children, recursive case
    int tempkey = node->key;
    int tempval = node->value;

    node->key = replacement->key;
    node->value = replacement->value;

    replacement->key = tempkey;
    replacement->value = tempval;

    Delete(replacement);
}*/
{
    Node<K, V>* u = GetClosest(node);
 
    // True when u and v are both black
    bool uvBlack = ((u == NULL || u->color == NodeColor::BLACK) && (node->color == NodeColor::BLACK));
    Node<K, V>* parent = node->parent;
 
    if (u == NULL) {
      // u is NULL therefore v is leaf
      if (node == _root) {
        // v is root, making root null
        _root = NULL;
      } else {
        if (uvBlack) {
          // u and v both black
          // v is leaf, fix double black at v
          FixDoubleBlack(node);
        } else {
          // u or v is red
          if (GetSibling(node) != NULL)
            // sibling is not null, make it red"
            GetSibling(node)->color = NodeColor::RED;
        }
 
        // delete v from the tree
        if (IsLeftChild(node)) {
          parent->leftChild = NULL;
        } else {
          parent->rightChild = NULL;
        }
      }
      delete node;
      return;
    }
 
    if (node->leftChild == NULL || node->rightChild == NULL) {
      // v has 1 child
      if (node == _root) {
        // v is root, assign the value of u to v, and delete u
        node->key = u->key;
        node->value = u->value;
        node->leftChild = node->rightChild = NULL;
        delete u;
      } else {
        // Detach v from tree and move u up
        if (IsLeftChild(node)) {
          parent->leftChild = u;
        } else {
          parent->rightChild = u;
        }
        delete node;
        u->parent = parent;
        if (uvBlack) {
          // u and v both black, fix double black at u
          FixDoubleBlack(u);
        } else {
          // u or v red, color u black
          u->color = NodeColor::BLACK;
        }
      }
      return;
    }
 
    // v has 2 children, swap values with successor and recurse
    int tempkey = node->key;
    int tempval = node->value;

    node->key = u->key;
    node->value = u->value;

    u->key = tempkey;
    u->value = tempval;

    Delete(u);
  }

// Double-black correction helper
template<typename K, typename V>
void RBTree<K, V>::FixDoubleBlack(Node<K, V>* node)
{
    if (node == _root)
      // Reached root
      return;
 
    Node<K, V>* sibling = GetSibling(node);
    Node<K, V>* parent = node->parent;
    if (sibling == NULL) {
      // No sibiling, double black pushed up
      FixDoubleBlack(parent);
    } 
    else {
      if (sibling->color == NodeColor::RED) {
        // Sibling red
        parent->color = NodeColor::RED;
        sibling->color = NodeColor::BLACK;
        if (IsLeftChild(sibling)) {
          // left case
          RightRotation(parent);
        } else {
          // right case
          LeftRotation(parent);
        }
        FixDoubleBlack(node);
      } else {
        // Sibling black
        if ( (sibling->leftChild != NULL && sibling->leftChild->color == NodeColor::RED) && (sibling->rightChild != NULL && sibling->rightChild->color == NodeColor::RED) ) {
          // at least 1 red children
          if (sibling->leftChild != NULL && sibling->leftChild->color == NodeColor::RED) {
            if (IsLeftChild(sibling)) {
              // left left
              sibling->leftChild->color = sibling->color;
              sibling->color = parent->color;
              RightRotation(parent);
            } else {
              // right left
              sibling->leftChild->color = parent->color;
              RightRotation(sibling);
              LeftRotation(parent);
            }
          } else {
            if (IsLeftChild(sibling)) {
              // left right
              sibling->rightChild->color = parent->color;
              LeftRotation(sibling);
              RightRotation(parent);
            } else {
              // right right
              sibling->rightChild->color = sibling->color;
              sibling->color = parent->color;
              LeftRotation(parent);
            }
          }
          parent->color = NodeColor::BLACK;
        } else {
          // 2 black children
          sibling->color = NodeColor::RED;
          if (parent->color == NodeColor::BLACK)
            FixDoubleBlack(parent);
          else
            parent->color = NodeColor::BLACK;
        }
      }
    }
  }
/*{
    // Exit case
    if(node == _root) return;

    // Find sibling of node;
    Node<K, V>* sibling;
    if(IsLeftChild(node)) sibling = node->parent->rightChild;
    else sibling = node->parent->leftChild;

    // No sibling, recurse on parent
    if(sibling == NULL) FixDoubleBlack(node->parent);

    else {
        // Sibling left child is red
        if((sibling->leftChild != NULL && sibling->leftChild->color == NodeColor::RED)) {
            if(IsLeftChild(sibling)) {
                sibling->leftChild->color = sibling->color;
                sibling->color = node->parent->color;

                RightRotation(node->parent);
            }
            else {
                sibling->leftChild->color = node->parent->color;

                RightRotation(sibling);
                LeftRotation(node->parent);
            }
        }
        // Sibling right child is red
        else if((sibling->rightChild != NULL && sibling->rightChild->color == NodeColor::RED)) {
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
        // Sibling has 2 black children
        else {
            sibling->color = NodeColor::RED;

            if(node->parent->color == NodeColor::BLACK) FixDoubleBlack(node->parent);
            else node->parent->color = NodeColor::BLACK;
        }
    }
}*/

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

// Recursive function to set ranks
template<typename K, typename V>
void RBTree<K, V>::SetRanks(Node<K, V>* current, int currentRank) 
{
    current->rank = currentRank + 1;

    if(current->rightChild != NULL) SetRanks(current->rightChild, currentRank + 1);
    if(current->leftChild != NULL) SetRanks(current->leftChild, currentRank + 1);
}

// Recursive function to set number of children of node
template<typename K, typename V>
void RBTree<K, V>::SetChildrenNumbers(Node<K, V>* current)
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
template<typename K, typename V>
Node<K, V>* RBTree<K, V>::RecursiveSelect(Node<K, V>* current, int position)
{
    if(current == NULL) return NULL;

    if(current->numChildrenLeft > position) return RecursiveSelect(current->leftChild, position);
    else if(current->numChildrenLeft < position) return RecursiveSelect(current->rightChild, position - current->numChildrenLeft - 1);
    else return current;
}